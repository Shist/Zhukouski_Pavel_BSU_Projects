#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "commons.h"

// Считает распределение в тексте

int
main(int argc, char** argv)
{
    if (2 != argc)
    {
        std::cerr << "must provide the size of the symbol";
        return 1;
    }
    int symbol_size = std::strtol(argv[1], nullptr, 10);
    if (symbol_size <= 0)
    {
        std::cerr << "incorrect size of the symbol: must be a positive number";
        return 1;
    }

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
    for (const auto& kv : occurrences)
        std::cout << kv.first << ' ' << std::setprecision(10) <<
        double(kv.second) / total_symbols << '\n';
}
