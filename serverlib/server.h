#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <thread>
#include <atomic>
#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include "networklib/message.h"
#include "networklib/connection.h"

class Server
{
public:
    typedef boost::signals2::signal<void(const Message::Activity&)>
        QuestionableActivityReceivedSignal;

    Server(boost::asio::io_service& ios);
    ~Server();

    std::uint32_t GetActivityCount() const;

    bool StartListening(uint16_t port);

    QuestionableActivityReceivedSignal& GetQuestionableActivityReceivedSignal();

private:
    typedef std::shared_ptr<std::thread> ThreadPointer;

    void AsyncAccept();

    void HandleAccept(const boost::system::error_code& ec);

    void HandleConnection(Connection::Pointer connection);

    boost::asio::io_service& m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::vector<Connection::Pointer> m_connections;
    std::list<ThreadPointer> m_threads;
    Connection::Pointer m_pendingConnection;
    QuestionableActivityReceivedSignal m_questionableActivityReceivedSignal;
    std::atomic_uint32_t m_activityCount;
};

#endif
