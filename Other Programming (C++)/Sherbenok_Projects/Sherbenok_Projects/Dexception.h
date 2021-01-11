#pragma once
#include <exception>
class Dexception : public std::exception {
public:
	Dexception(const char* const message) : exception(message) {}
	Dexception(const Dexception& right) : exception(right) {}
};