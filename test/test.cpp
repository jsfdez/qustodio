#define BOOST_TEST_MODULE SimpleTests
#include <boost/test/unit_test.hpp>
#include <thread>
#include <future>
#include <functional>

#include "serverlib/server.h"

BOOST_AUTO_TEST_CASE(Nothing)
{
}

BOOST_AUTO_TEST_CASE(SpawnServer)
{
    std::packaged_task<int()> task([]()
    {
        boost::asio::io_service ios;
        Server server(ios);
        BOOST_CHECK(server.StartListening(12345));
        return ios.run_one();
    });
    std::future<int> future = task.get_future();
    std::thread thread(std::move(task));

    boost::asio::io_service ios;
    boost::asio::ip::tcp::resolver resolver(ios);
    boost::asio::ip::tcp::resolver::query query("localhost", "12345");
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query), end;
    boost::asio::ip::tcp::socket socket(ios);
    boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && it != end)
    {
        socket.close();
        socket.connect(*it++, error);
    }
    socket.close();
    BOOST_CHECK(!error);
    thread.join();
}
