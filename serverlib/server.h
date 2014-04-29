#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "networklib/connection.h"

class Server
{
public:
    Server(boost::asio::io_service& ios);

    bool StartListening(uint16_t port);

private:
    void AsyncAccept();

    void HandleAccept(const boost::system::error_code& ec);

    boost::asio::io_service& m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::vector<Connection::Pointer> m_connections;
    Connection::Pointer m_pendingConnection;
};

#endif
