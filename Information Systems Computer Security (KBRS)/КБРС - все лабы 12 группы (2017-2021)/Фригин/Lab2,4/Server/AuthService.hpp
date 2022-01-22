#pragma once
#include <string>

class AuthService
{
public:
    static bool Check(const std::string &login, const std::string &password);
};
