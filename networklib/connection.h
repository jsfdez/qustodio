#pragma once

#include <boost/asio.hpp>

class Connection
{
public:
    Connection(boost::asio::io_service& ios);

    typedef std::shared_ptr<Connection> Pointer;

    static Connection* Create(boost::asio::io_service& ios);

    boost::asio::ip::tcp::socket& GetSocket();

private:
    boost::asio::ip::tcp::socket m_socket;
};
