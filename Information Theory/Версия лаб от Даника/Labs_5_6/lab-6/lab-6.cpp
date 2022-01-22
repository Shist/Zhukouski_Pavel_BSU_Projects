#include <bits/stdc++.h>

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

struct trie_node
{
    int number;
    trie_node *children[2];
    trie_node(): number(0), children{ nullptr, nullptr } {}
};

void
trie_insert_child(trie_node *node, int bit, int number)
{
    node->children[bit] = new trie_node();
    node->children[bit]->number = number;
}

void
trie_destroy(trie_node *root_node)
{
    if (!root_node)
        return;
    trie_destroy(root_node->children[0]);
    trie_destroy(root_node->children[1]);
    delete root_node;
}

struct lz_state {
    int curr_word;
    int total_bits;
    trie_node *root_node, *curr_node;
    int lz_length;
    lz_state(): curr_word(0), total_bits(0), root_node(new trie_node()), 
        curr_node(root_node), lz_length(0) {}
    ~lz_state() { trie_destroy(root_node); }
};

void
lz_state_change_bit(lz_state &state, int bit)
{
    ++state.total_bits;
    trie_node *child = state.curr_node->children[bit];
    if (child) {
        state.curr_node = child;
        return;
    } 

    state.lz_length += elias_code(state.curr_node->number).length() + 1;
    ++state.curr_word;
    trie_insert_child(state.curr_node, bit, state.curr_word);
    state.curr_node = state.root_node;
}

void
lz_state_change(lz_state &state, int c)
{
    for (int i = 8 * sizeof(char) - 1; i >= 0; --i)
        lz_state_change_bit(state, ((1 << i) & c) >> i);
}

void
lz_finish(lz_state &state)
{
    while (state.root_node != state.curr_node)
        lz_state_change_bit(state, 0);
}

double
lz_upper_bound(int n)
{
    return n / std::log2(n);
}

int
main()
{
    char c;
    lz_state state;
    while (std::cin.get(c)) {
        lz_state_change(state, c);
    }
    lz_finish(state);

    std::cout << "The number of source bits is " << state.total_bits << '\n';
    std::cout << "The number of bits after LZ encoding is " <<
        state.lz_length << '\n';
    std::cout << "The number of unique words in the text is " <<
        state.curr_word << '\n';
    std::cout << "The upper bound in the LZ inequality is " <<
        lz_upper_bound(state.total_bits) << '\n';
}
