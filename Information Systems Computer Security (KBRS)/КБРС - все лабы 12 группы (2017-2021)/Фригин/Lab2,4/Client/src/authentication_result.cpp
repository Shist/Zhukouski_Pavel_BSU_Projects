#include "client/authentication_result.h"


AuthenticationResult::AuthenticationResult(QObject *parent, QString login, bool is_authenticated, QString reason)
    : QObject(parent), _login(login), _isAuthenticated(is_authenticated), _reason(reason)
{}

AuthenticationResult &AuthenticationResult::operator=(AuthenticationResult &&other) noexcept
{
    _login = other._login;
    _isAuthenticated = other._isAuthenticated;
    _reason = other._reason;
}

QString AuthenticationResult::login()
{
    return _login;
}

bool AuthenticationResult::isAuthenticated()
{
    return _isAuthenticated;
}

QString AuthenticationResult::reason()
{
    return _reason;
}
