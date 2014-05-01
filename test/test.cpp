#define BOOST_TEST_MODULE SimpleTests
#include <boost/test/unit_test.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <future>
#include <fstream>
#include <functional>

#include "serverlib/server.h"
#include "clientlib/client.h"

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

struct CreateServer
{
    ~CreateServer()
    {
        server.ios.stop();
        server.thread.join();
    }

    struct _Server
    {
        _Server() : instance(ios)
        {
            BOOST_CHECK(instance.StartListening(12345));
            auto bind = boost::bind(&boost::asio::io_service::run, &ios);
            thread = std::thread(bind);
        }

        std::thread thread;
        boost::asio::io_service ios;
        Server instance;
    } server;

    struct _Client
    {
        _Client() : instance(ios)
        {
            instance.Connect("localhost", 12345);
        }
        boost::asio::io_service ios;
        Client instance;
    } client;
};

BOOST_FIXTURE_TEST_CASE(ConnectDisconnect, CreateServer)
{
    BOOST_CHECK(client.instance.IsOpen());
    client.instance.Disconnect();
    BOOST_CHECK(!client.instance.IsOpen());
}

BOOST_FIXTURE_TEST_CASE(FilterFile, CreateServer)
{
    bool found = false;
    std::function<void(const Message::Activity& activity)> callback = [&found](
            const Message::Activity&)
    {
        found = true;
    };
    BOOST_CHECK(client.instance.IsOpen());
    client.instance.AddOffendingWord("porn").AddOffendingWord("xxx")
            .AddOffendingWord("sex").AddOffendingWord("Bieber");
    client.instance.GetQuestionableActivityFoundSignal().connect(callback);
    std::fstream stream("logs/sample.log");
    BOOST_REQUIRE(stream.is_open());
    BOOST_CHECK(client.instance.Filter(stream));
    BOOST_CHECK(found);
    client.instance.Disconnect();
    BOOST_CHECK(!client.instance.IsOpen());
}
