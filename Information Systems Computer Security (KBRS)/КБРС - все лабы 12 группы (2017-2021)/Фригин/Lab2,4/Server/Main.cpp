#include <iostream>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "Server.hpp"
#include "TimerService.hpp"

int main (int argc, char **argv)
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage:" << std::endl << "    <server_executable> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_context ioContext;
        Server server (ioContext, std::atoi (argv[1]));

        while (true)
        {
            try
            {
                ioContext.poll ();
                TimerService::Step ();
            }
            catch (std::runtime_error &error)
            {
                BOOST_LOG_TRIVIAL (error) << "Caught error: " << error.what ();
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what () << "\n";
    }

    return 0;
}
