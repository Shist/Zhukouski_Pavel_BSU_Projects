#include <bits/stdc++.h>
#include "commons.h"

int
main(int argc, char **argv)
{
    if (3 != argc)
        errx(1, "please provide two files with distributions");

    std::ifstream f_str(argv[1]), g_str(argv[2]);
    std::unordered_map<std::string, double> f_distrib = read_distrib(f_str);
    std::unordered_map<std::string, double> g_distrib = read_distrib(g_str);

    for (const auto &f_kv : f_distrib)
        if (g_distrib.find(f_kv.first) == g_distrib.end())
            errx(1, "the g domain isn't a superset of the f domain");

    std::cout << "The relative entropy h(f||g) equals " <<
        std::accumulate(
            g_distrib.begin(), g_distrib.end(), 0.0,
            [&] (double result, const std::pair<std::string, double> &g_kv){
                auto f_kv = f_distrib.find(g_kv.first);
                double f_prob (f_kv == f_distrib.end() ? 0.0 : f_kv->second);
                return result + f_prob * std::log2(f_prob / g_kv.second);
            }
        ) << '\n';
}
