#include "Server.hpp"
#include "Session.hpp"
#include <boost/log/trivial.hpp>

Server::Server (boost::asio::io_context &ioContext, short port)
    : ioContext_ (ioContext),
      acceptor_ (ioContext, boost::asio::ip::tcp::endpoint (boost::asio::ip::tcp::v4 (), port))
{
    StartAccept ();
}

void Server::StartAccept ()
{
    if (!continueAccept_)
    {
        return;
    }

    auto *newSession = new Session (ioContext_);
    BOOST_LOG_TRIVIAL(info) << "Server: Waiting for next client...";

    acceptor_.async_accept (newSession->GetSocket (),
                            [this, newSession] (const boost::system::error_code &error)
                            {
                                if (!error)
                                {
                                    newSession->Start ();
                                }
                                else
                                {
                                    delete newSession;
                                }

                                StartAccept ();
                            });
}
