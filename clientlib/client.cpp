#include "client.h"

#include <regex>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>

#include "commonlib/message.h"
#include "commonlib/activity.h"

Client::Client(boost::asio::io_service& ios)
    : Connection(ios)
{
    m_questionableActivityFoundSignal.connect(std::bind(&Client::SendQuestionableActivity, this,
		std::placeholders::_1));
}

bool Client::Connect(const std::string& host, uint16_t port)
{
    boost::asio::ip::tcp::resolver resolver(GetIoService());
    boost::asio::ip::tcp::resolver::query query(host, 
        boost::lexical_cast<std::string>(port));
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query), end;
    boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && it != end)
    {
        GetSocket().close();
        GetSocket().connect(*it++, error);
    }
    return !error;
}

bool Client::Filter(std::istream &stream)
{
    while(!stream.eof())
    {
        Activity activity;
        stream >> activity;
        if (stream.eof())
            return true;
        else if (stream.fail())
        {
            std::cerr << "Parse error" << std::endl;
            return false;
        }
        std::regex rx(m_filterExpression, std::regex_constants::icase);
        if (std::regex_search(activity.url.begin(),
                              activity.url.end(), rx))
        {
            m_questionableActivityFoundSignal(activity);
        }
    }
    return true;
}

Client::QuestionableActivityFoundSignal &Client::GetQuestionableActivityFoundSignal()
{
    return m_questionableActivityFoundSignal;
}

Client::ServerAnswerReceivedSignal& Client::GetServerAnswerReceivedSignal()
{
    return m_serverAnswerReceivedSignal;
}

Client& Client::AddOffendingWord(const std::string &word)
{
    if (!word.empty())
    {
        m_offendingWords.push_back(word);
        UpdateFilterExpression();
    }
    return *this;
}

void Client::UpdateFilterExpression()
{
    m_filterExpression = boost::algorithm::join(m_offendingWords, "|");
}

void Client::SendQuestionableActivity(const Activity& activity)
{
	if (!IsOpen())
		return;

    Message message(activity);
    try 
    {
        message.Send(GetSocket());
        message.Receive(GetSocket());
        BOOST_ASSERT(message.GetActivityCount().is_initialized());
        switch(message.GetType())
        {
        case Message::Type::STORED:
        case Message::Type::NOT_STORED:
            m_serverAnswerReceivedSignal(
                static_cast<ServerMessageType>(message.GetType()), 
                *message.GetActivityCount());
            break;
        case Message::Type::QUESTIONABLE_ACTIVITY_FOUND:
        case Message::Type::INVALID:
            BOOST_ASSERT(false);
            break;
        }
    }
    catch (boost::system::system_error&)
    {
        // Error or EOF handling
        Disconnect();
    }
}
