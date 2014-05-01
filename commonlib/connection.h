#pragma once

#include <boost/asio.hpp>

class Connection
{
public:
    typedef std::shared_ptr<Connection> Pointer;

    Connection(boost::asio::io_service& ios);

    boost::asio::ip::tcp::socket& GetSocket();

    bool IsOpen() const;
    void Disconnect();

	void PrepareToRead();
	void Write();

protected:
    boost::asio::io_service& GetIoService();

private:
    boost::asio::ip::tcp::socket m_socket;
};
