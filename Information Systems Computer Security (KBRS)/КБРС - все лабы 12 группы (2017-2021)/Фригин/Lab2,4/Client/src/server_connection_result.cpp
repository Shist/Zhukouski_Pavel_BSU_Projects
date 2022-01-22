#include "client/server_connection_result.h"


ServerConnectionResult::ServerConnectionResult(QObject *parent, QString address, QString port, bool isConnected, QString reason)
    : QObject(parent), _address(address), _port(port), _isConnected(isConnected), _reason(reason)
{}

ServerConnectionResult &ServerConnectionResult::operator=(ServerConnectionResult &&other) noexcept
{
    _address = other._address;
    _port = other._port;
    _isConnected = other._isConnected;
    _reason = other._reason;
}

bool ServerConnectionResult::isConnected()
{
    return _isConnected;
}

QString ServerConnectionResult::reason()
{
    return _reason;
}

QString ServerConnectionResult::address()
{
    return _address;
}

QString ServerConnectionResult::port()
{
    return _port;
}

