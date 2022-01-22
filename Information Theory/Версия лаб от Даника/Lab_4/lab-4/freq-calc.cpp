#include <bits/stdc++.h>
#include <err.h>

std::istream &
read_symbol(std::istream &str, std::string &symbol, int symbol_size)
{
    char symbol_char;
    while (symbol_size > 0 && str.get(symbol_char)) {
        symbol += symbol_char;
        --symbol_size;
    }
    return str;
}

int
main(int argc, char **argv)
{
    if (2 != argc)
        errx(1, "must provide the size of the symbol");
    int symbol_size = std::strtol(argv[1], nullptr, 10);
    if (symbol_size <= 0)
        errx(1, "incorrect size of the symbol: must be a positive number");
    
    std::cout << symbol_size << '\n';
    std::unordered_map<std::string, int> occurrences;
    int total_symbols = 0;
    std::string curr;
    while (read_symbol(std::cin, curr, symbol_size)) {
        ++total_symbols;
        if (occurrences.find(curr) == occurrences.end())
            occurrences[curr] = 0;
        ++occurrences[curr];
        curr.clear();
    }
    std::cerr << total_symbols << '\n';
    for (const auto &kv : occurrences)
        std::cout << kv.first << ' ' << std::setprecision(10) <<
            double(kv.second) / total_symbols << '\n';
}
