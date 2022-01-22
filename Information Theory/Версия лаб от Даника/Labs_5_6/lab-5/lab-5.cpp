#include <bits/stdc++.h>
#include <err.h>

int
binary_length(unsigned long long n)
{
    int length = 1;
    while ((1ULL << length) <= n)
        ++length;
    return length;
}

std::string
binary_code(unsigned int n, const int len)
{
    if (0 == len)
        return std::string();

    return binary_code(n / 2, len - 1) + std::to_string(n % 2);
}

std::string
prefix_code(unsigned int n)
{
    int l = binary_length(n);
    return binary_code(0, l - 1) + binary_code(n, l);
}

std::string
elias_code(unsigned int n)
{
    int l = binary_length(n);
    return prefix_code(l) + binary_code(n, l - 1);
}

std::istream &
read_aligned_binary_block(std::istream &str, std::string &block, int phrase_length)
{
    char next_char;
    while (str.get(next_char)) {
        block += binary_code(next_char, sizeof(char));
        if (0 == block.length() % phrase_length)
            break;
    }
    while (0 != block.length() % phrase_length) {
        block += binary_code(0, sizeof(char));
    }
    return str;
}

int
main(int argc, char **argv)
{
    if (2 != argc)
        errx(1, "provide the length of the phrase");
    int phrase_length = std::strtol(argv[1], nullptr, 10);
    if (phrase_length < 1)
        errx(1, "the length of the phrase must be a number not less than 1");

    std::list<std::string> phrase_deck;
    int phrase_number = 1 << phrase_length;
    for (int i = 0; i < phrase_number; ++i)
        phrase_deck.push_back(binary_code(i, phrase_length));
    
    std::string block, phrase;
    int total_code_length = 0, total_code_number = 0;
    while (read_aligned_binary_block(std::cin, block, phrase_length)) {
        for (size_t i = 0; i < block.length(); i += phrase_length) {
            int pos_num = 0;
            for (auto pos = phrase_deck.begin(); pos != phrase_deck.end(); ++pos) {
                ++pos_num;
                if (0 == block.compare(i, phrase_length, *pos)) {
                    phrase = std::move(*pos);
                    phrase_deck.erase(pos);
                    phrase_deck.push_front(std::move(phrase));
                    ++total_code_number;
                    total_code_length += elias_code(pos_num).length();
                    break;
                }
            }
        }
        block.clear();
    }

    std::cout << "The average length of the code word is " << 
        (double)(total_code_length) / total_code_number << '\n';
}
