#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <thread>
#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "networklib/connection.h"

class Server
{
public:
    Server(boost::asio::io_service& ios);
    ~Server();

    bool StartListening(uint16_t port);

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
};

#endif
