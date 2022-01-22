#include <iostream>
#include <string>
#include <list>

/*
Алгоритм Рябко-Элайеса
Пример. Предположим, что все фразы имеют длину k = 2 исходных символов, а исходная нумерация фраз соответствует возрастанию их
значений: [00] → 1, [01] → 2, [10] → 3, [11] → 4. Тогда последовательность
10, 10, 01, 11, 11, ...
кодируется следующим образом. Вместо первой фразы 10 передается ее
номер 3 (равный BElias(3) = 0101), а список фраз переупорядочивается:
10 → 1, 00 → 2, 01 → 3, 11 → 4. Вместо второй фразы 10 передается ее новый номер 1 (равный BElias(1) = 1), а список фраз остается
без изменений. С приходом фразы 01 передается ее номер 3 (равный
BElias(3) = 0101), а список фраз снова переупорядочивается: 01 → 1,
10 → 2, 00 → 3, 11 → 4. Фразе 11 соответствует номер 4 (равный
BElias(4) = 01100) и новый список: 11 → 1, 01 → 2, 10 → 3, 00 → 4.
Следующей фразе 11 соответствует уже номер 1 (равный BElias(1) = 1),
а список остается без изменений. Таким образом, код, построенный по
алгоритму Рябко – Элайеса, имеет следующий вид:
0101, 1, 0101, 01100, 1, ...,
где разделяющие запятые могут быть, конечно, опущены, так как код
BElias(n) является префиксным.

P.S. Для завершения ввода текста нужно нажать Ctrl+Z
*/

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

std::istream&
read_aligned_binary_block(std::istream& str, std::string& block, int phrase_length)
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
main(int argc, char** argv)
{
    if (2 != argc)
    {
        std::cerr << "provide the length of the phrase";
        return 1;
    }
    int phrase_length = std::strtol(argv[1], nullptr, 10);
    if (phrase_length < 1)
    {
        std::cerr << "the length of the phrase must be a number not less than 1";
        return 1;
    }

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
