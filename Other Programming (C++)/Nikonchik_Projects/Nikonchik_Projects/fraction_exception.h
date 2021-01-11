#pragma once
#include <exception>

class fraction_exception : public std::exception
{
public:
	fraction_exception(const char* const msg) : std::exception(msg) {}
	fraction_exception(const fraction_exception& right) : std::exception(right) {}
};