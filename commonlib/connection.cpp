#include "connection.h"

Connection::Connection(boost::asio::io_service& ios)
: m_socket(ios)
{}

boost::asio::ip::tcp::socket& Connection::GetSocket()
{
    return m_socket;
}

boost::asio::io_service& Connection::GetIoService()
{
    return m_socket.get_io_service();
}

bool Connection::IsOpen() const
{
    return m_socket.is_open();
}

void Connection::Disconnect()
{
    m_socket.close();
}
