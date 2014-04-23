#include <iostream>
#include <stdlib.h>
#include <functional>

#include "networklib/server.h"

int main(int argc, char** argv)
{
    boost::asio::io_service ios;
    Server server(ios);

    if (server.StartListening(PORT))
    {

    }

    return EXIT_SUCCESS;
}
