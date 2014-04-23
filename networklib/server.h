#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

class Server
{
public:
    class Connection : public boost::enable_shared_from_this<Connection>
    {
    public:
		Connection(boost::asio::io_service& ios);

		typedef boost::shared_ptr<Connection> Pointer;

        static Connection* Create(boost::asio::io_service& ios);

        boost::asio::ip::tcp::socket& GetSocket();
    
	private:
        boost::asio::ip::tcp::socket m_socket;
    };

    Server(boost::asio::io_service& ios);

    bool StartListening(uint16_t port);

private:
//    void HandleAccept(Connection* connection,
//                      const boost::system::error_code& ec);
    void HandleAccept(const boost::system::error_code& ec);

    boost::asio::io_service& m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::vector<Connection::Pointer> m_connections;
    Connection::Pointer m_pendingConnection;
};


#endif
