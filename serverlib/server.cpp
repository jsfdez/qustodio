#include "server.h"

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/exception/all.hpp>

#include "rapidjson/document.h"
#include "commonlib/message.h"

#define FOREVER for(;;)

Server::Server(boost::asio::io_service& ios)
    : m_ios(ios)
    , m_acceptor(m_ios)
    , m_activityCount(0)
    , m_closing(false)
    , m_showActivitiesThread(std::bind(&Server::ShowActivities, this))
{
    m_questionableActivityReceivedSignal.connect(std::bind(&Server::AddActivity,
        this, std::placeholders::_1));
}

Server::~Server()
{
    for (ThreadPointer& thread : m_threads)
    {
        if (thread->joinable())
            thread->join();
    }
    m_closing = true;
    m_showActivitiesThread.join();
}

std::uint32_t Server::GetActivityCount() const
{
    uint32_t count = m_activityCount;
    return count;
}

bool Server::StartListening(uint16_t port)
{
    boost::system::error_code ec;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    m_acceptor.open(endpoint.protocol(), ec);
    if (ec)
        return false;
    m_acceptor.bind(endpoint, ec);
    if (ec)
        return false;
    m_acceptor.listen(boost::asio::socket_base::max_connections, ec);
    if (ec)
        return false;

    AsyncAccept();
    return true;
}

Server::QuestionableActivityReceivedSignal& Server::
    GetQuestionableActivityReceivedSignal()
{
    return m_questionableActivityReceivedSignal;
}

void Server::AsyncAccept()
{
    m_pendingConnection = std::make_shared<Connection>(m_ios);
    auto callback = boost::bind(&Server::HandleAccept, this,
        boost::asio::placeholders::error);
    m_acceptor.async_accept(m_pendingConnection->GetSocket(), callback);
}

void Server::HandleAccept(const boost::system::error_code& ec)
{
    if (!ec)
    {
        auto function = std::bind(&Server::HandleConnection, this,
            m_pendingConnection);
        m_threads.emplace_back(new std::thread(function));
        AsyncAccept();
    }
}

void Server::HandleConnection(Connection::Pointer connection)
{
    try
    {
        FOREVER
        {
            Message message;
            message.Receive(connection->GetSocket());
            BOOST_ASSERT(message.GetType() == Message::Type::QUESTIONABLE_ACTIVITY_FOUND);
            message.SetType(Message::Type::STORED); // NOT_STORED?!?!?
            message.SetActivityCount(++m_activityCount);
            m_questionableActivityReceivedSignal(message.GetActivity());
            message.Send(connection->GetSocket());
        }
    }
    catch (boost::system::system_error&)
    {
        // Error or EOF handling
        connection->Disconnect();
    }
}

void Server::ShowActivities()
{
    while(!m_closing)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Server::AddActivity(const Activity &activity)
{
    std::lock_guard<std::mutex> lg(m_activitiesQueueMutex);
    m_activitiesQueue.push(std::make_pair(activity, 0));
}
