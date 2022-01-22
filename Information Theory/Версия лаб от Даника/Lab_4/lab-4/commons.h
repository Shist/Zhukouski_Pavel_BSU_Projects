#ifndef _LAB4_COMMONS_H_
#define _LAB4_COMMONS_H_

#include <bits/stdc++.h>
#include <err.h>

std::istream &read_symbol(std::istream &probin, std::string &symbol, int symbol_len);
std::unordered_map<std::string, double> read_distrib(std::istream &probin);

#endif // _LAB4_COMMONS_H_
