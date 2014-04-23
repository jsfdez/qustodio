#include "server.h"

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

Server::Server(boost::asio::io_service& ios)
    : m_ios(ios)
    , m_acceptor(m_ios)
{
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

//    auto connection = Connection::Create(m_ios);
    m_pendingConnection = boost::make_shared<Connection>(
                Connection::Create(m_ios));
//    auto callback = boost::bind(&Server::HandleAccept, this, connection,
//                      boost::asio::placeholders::error);
    m_acceptor.async_accept(m_pendingConnection->GetSocket(),
                            &Server::HandleAccept);
//    m_acceptor.async_accept(connection->GetSocket(), callback);
    return true;
}

//void Server::HandleAccept(Server::Connection* connection,
//                          const boost::system::error_code& ec)
//{
//    std::cout << "hello world!!" << std::endl;
//    if (!ec)
//    {
//        m_connections.push_back(connection->shared_from_this());
//    }
//}

void Server::HandleAccept(const boost::system::error_code& ec)
{
    std::cout << "hello world!!" << std::endl;
    if (!ec)
    {
        m_connections.push_back(m_pendingConnection);
    }
}

Server::Connection* Server::Connection::Create(boost::asio::io_service& ios)
{
    return new Connection(ios);
}

boost::asio::ip::tcp::socket&Server::Connection::GetSocket()
{
    return m_socket;
}

Server::Connection::Connection(boost::asio::io_service& ios)
    : m_socket(ios)
{
}
