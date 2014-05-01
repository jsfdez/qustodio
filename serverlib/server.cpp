#include "server.h"

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/exception/all.hpp>

#include "rapidjson/document.h"
#include "networklib/message.h"

Server::Server(boost::asio::io_service& ios)
: m_ios(ios)
, m_acceptor(m_ios)
{}

Server::~Server()
{
    for (ThreadPointer& thread : m_threads)
    {
        if (thread->joinable())
            thread->join();
    }
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
        for (;;)
        {
            Message message;
            message.Receive(connection->GetSocket());
            message.SetType(Message::Type::ACKNOWLEDGE);

        }
    }
    catch (boost::system::system_error&)
    {
        // Error or EOF handling
        connection->Disconnect();
    }
}
