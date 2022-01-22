#include "commons.h"

std::istream&
read_symbol(std::istream& probin, std::string& symbol, int symbol_len)
{
    char next_char;
    for (; symbol_len > 0; --symbol_len) {
        probin.get(next_char);
        symbol += next_char;
    }
    return probin;
}

std::unordered_map<std::string, double>
read_distrib(std::istream& probin)
{
    std::unordered_map<std::string, double> msg_probs;
    int symbol_len;
    std::string symbol;
    double curr_prob, total_prob = 0;
    probin >> symbol_len;
    probin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (read_symbol(probin, symbol, symbol_len) >> curr_prob) {
        msg_probs[symbol] = curr_prob;
        symbol.clear();
        total_prob += curr_prob;
        if (total_prob - 1.0 > 1e-6)
        {
            std::cerr << "total probability is %lf > 1";
            exit(1);
        }
        probin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (std::abs(1.0 - total_prob) > 1e-6)
    {
        std::cerr << "the probabilities don't sum up to 1";
        exit(1);
    }
    return msg_probs;
}

