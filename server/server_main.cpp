#include <iostream>
#include <stdlib.h>
#include <functional>

#include "serverlib/server.h"

int main(int argc, char** argv)
{
    boost::asio::io_service ios;
    boost::asio::io_service::work work(ios);
    Server server(ios);

    if (server.StartListening(PORT))
    {
        ios.run();
    }

    return EXIT_SUCCESS;
}
