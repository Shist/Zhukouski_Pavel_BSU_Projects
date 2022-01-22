#pragma once
#include <iostream>
#include <boost/asio.hpp>

class Server final
{
public:
    Server (boost::asio::io_context &ioContext, short port);

private:
    void StartAccept ();

    bool continueAccept_ = true;
    boost::asio::io_context &ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
};
