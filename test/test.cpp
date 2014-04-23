#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SimpleTests
#include <boost/test/unit_test.hpp>

#include "networklib/server.h"

BOOST_AUTO_TEST_CASE(Nothing)
{
}

BOOST_AUTO_TEST_CASE(SpawnServer)
{
    boost::asio::io_service ios;
    boost::asio::io_service::work work(ios);
    Server server(ios);
    BOOST_CHECK(server.StartListening(12345));
    ios.run();
}
