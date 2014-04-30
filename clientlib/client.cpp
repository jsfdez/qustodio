#include "client.h"

#include <regex>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>

#include "rapidjson/document.h"

std::istream& operator>>(std::istream &is, Client::Activity &a)
{
//    is >> a.address >> a.url >> a.timestamp;
    std::string key;
    is >> key >> a.address;
    if (key != "device:")
    {
        is.setf(std::ios_base::failbit);
        return is;
    }
    is >> key >> a.url;
    if (key != "url:")
    {
        is.setf(std::ios_base::failbit);
        return is;
    }
    is >> key >> a.timestamp;
    if (key != "timestamp:")
        is.setf(std::ios_base::failbit);
    return is;
}

Client::Client(boost::asio::io_service& ios)
    : Connection(ios)
{
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
            m_questionableActivityFound(activity);
        }
    }
    return true;
}

Client::QuestionableActivityFoundSignal &Client::GetQuestionableActivityFoundSignal()
{
    return m_questionableActivityFound;
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

	rapidjson::Document document;
	rapidjson::Value address, url, timestamp;
	document.SetObject();
	address.SetString(activity.address.c_str(), document.GetAllocator());
	url.SetString(activity.url.c_str(), document.GetAllocator());
	timestamp.SetUint64(activity.timestamp);
	//document.AddMember("address", activity.address.c_str(), document.GetAllocator());
	//document.AddMember("url", activity.url.c_str(), document.GetAllocator());
	//document.AddMember("timestamp", );
}
