#include "connection.h"

Connection* Connection::Create(boost::asio::io_service& ios)
{
    return new Connection(ios);
}

boost::asio::ip::tcp::socket& Connection::GetSocket()
{
    return m_socket;
}

Connection::Connection(boost::asio::io_service& ios)
: m_socket(ios)
{}
