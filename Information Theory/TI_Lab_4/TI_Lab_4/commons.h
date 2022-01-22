#ifndef _LAB4_COMMONS_H_
#define _LAB4_COMMONS_H_

#include <iostream>
#include <unordered_map>

std::istream& read_symbol(std::istream& probin, std::string& symbol, int symbol_len);
std::unordered_map<std::string, double> read_distrib(std::istream& probin);

#endif // _LAB4_COMMONS_H_
