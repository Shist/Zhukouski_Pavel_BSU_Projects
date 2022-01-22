#include <bits/stdc++.h>
#include "commons.h"

struct msg_node
{
    std::string symbol;
    std::string code;
};

struct huffman_node
{
    double node_prob;
    std::list<msg_node> msgs;
};

struct huffman_node_cmp
{
    bool operator()(const huffman_node &a, const huffman_node &b)
        { return a.node_prob > b.node_prob; }
};

huffman_node
merge_huffman_nodes(huffman_node &a, huffman_node &b)
{
    huffman_node result { a.node_prob + b.node_prob };
    for (auto &msg : a.msgs)
        msg.code = '0' + msg.code;
    for (auto &msg : b.msgs)
        msg.code = '1' + msg.code;
    result.msgs = std::move(a.msgs);
    result.msgs.splice(result.msgs.begin(), b.msgs);
    return result;
}

std::unordered_map<std::string, std::string>
huffman_construct(const std::unordered_map<std::string, double> &msg_probs)
{
    std::priority_queue<huffman_node, std::vector<huffman_node>, 
        huffman_node_cmp> node_heap;
    for (const auto &kv : msg_probs) {
        msg_node msg { kv.first };
        huffman_node leaf { kv.second };
        leaf.msgs.push_back(std::move(msg));
        node_heap.push(std::move(leaf));
    }
    
    while (node_heap.size() > 1) {
        huffman_node first = node_heap.top();
        node_heap.pop();
        huffman_node second = node_heap.top();
        node_heap.pop();
        node_heap.push(merge_huffman_nodes(first, second));
    }

    huffman_node root = std::move(node_heap.top());
    std::unordered_map<std::string, std::string> result;
    for (auto &msg : root.msgs)
        result[msg.symbol] = std::move(msg.code);

    return result;
}

double
average_length(
    const std::unordered_map<std::string, std::string> &huffman_codes, 
    const std::unordered_map<std::string, double> &msg_probs
)
{
    return std::accumulate(
        msg_probs.begin(), msg_probs.end(), 0.0,
        [&] (double result, const std::pair<std::string, double> &kv) {
            return result + kv.second * huffman_codes.find(kv.first)->second.length();
        } 
    );
}

double
source_entropy(const std::unordered_map<std::string, double> &msg_probs)
{
    return std::accumulate(
        msg_probs.begin(), msg_probs.end(), 0.0,
        [] (double result, const std::pair<std::string, double> &kv) {
            return result - kv.second * std::log2(kv.second);
        }
    );
}

int
huffman_length(
    const std::string &text, 
    const std::unordered_map<std::string, std::string> &huffman_codes
)
{
    int result = 0;
    int symbol_length = huffman_codes.begin()->first.length();
    for (size_t i = 0; i < text.length(); i += symbol_length)
        result += huffman_codes.find(text.substr(i, symbol_length))->second.length();
    return result;
}

std::string
read_text(std::istream &txtin, int symbol_length)
{
    std::string text;
    std::getline(txtin, text);
    while (text.length() % symbol_length)
        text.pop_back();
    return text;
}

int
main(int argc, char **argv)
{
    if (3 != argc)
        errx(1, "need exactly two files: probability one and text one");

    std::ifstream probin(argv[1]), txtin(argv[2]);
    std::unordered_map<std::string, double> msg_probs = read_distrib(probin);
    std::string text = read_text(txtin, msg_probs.begin()->first.length());
    probin.close(), txtin.close();
    
    auto huffman_codes = huffman_construct(msg_probs);
    
    std::cout << "The average length of the code is " 
        << average_length(huffman_codes, msg_probs) << '\n';
    std::cout << "The entropy of the source is "
        << source_entropy(msg_probs) << '\n';
    std::cout << "The length of the source text is "
        << text.length() * 8 << " bits\n";
    std::cout << "The length of Huffman-encoded text is "
        << huffman_length(text, huffman_codes) << " bits\n"; 
}
