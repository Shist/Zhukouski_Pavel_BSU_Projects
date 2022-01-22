#include <bits/stdc++.h>
#include <err.h>

struct msg_node
{
    int num;
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

std::vector<std::string>
huffman_construct(const std::vector<double> &msg_probs)
{
    std::priority_queue<huffman_node, std::vector<huffman_node>, 
        huffman_node_cmp> node_heap;
    for (int i = 0; i < msg_probs.size(); ++i) {
        msg_node msg { i };
        huffman_node leaf { msg_probs[i] };
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

    huffman_node root = node_heap.top();
    std::vector<std::string> result(msg_probs.size());
    for (auto &msg : root.msgs)
        result[msg.num] = std::move(msg.code);

    return result;
}

int
number_of_digits(int num)
{
    int result = 0;
    do {
        ++result; 
        num /= 10;
    } while (num > 0);
    return result;
}

double
average_length(
    const std::vector<std::string> &huffman_codes, 
    const std::vector<double> &msg_probs
)
{
    double result = 0;
    for (int i = 0; i < huffman_codes.size(); ++i)
        result += huffman_codes[i].length() * msg_probs[i];
    return result;
}

double
source_entropy(const std::vector<double> &msg_probs)
{
    double result = 0;
    for (int i = 0; i < msg_probs.size(); ++i)
        result += -msg_probs[i] * std::log2(msg_probs[i]);
    return result;
}

int
main()
{
    std::vector<double> msg_probs;
    double curr_prob, total_prob = 0;
    while (std::cin >> curr_prob) {
        msg_probs.push_back(curr_prob);
        total_prob += curr_prob;
        if (total_prob > 1.0)
            errx(1, "total probability is %lf > 1", total_prob);
    }
    if (1.0 != total_prob)
        errx(1, "the probabilities don't sum up to 1");

    auto huffman_codes = huffman_construct(msg_probs);
    std::cout << "The Huffman codes for the messages are as follows:\n";
    int places = number_of_digits(msg_probs.size());
    for (int i = 0; i < huffman_codes.size(); ++i)
        std::cout << std::setw(places) << i << " | " << huffman_codes[i] << '\n';

    std::cout << "The average length of the code is " 
        << average_length(huffman_codes, msg_probs) << '\n';
    std::cout << "The entropy of the source is "
        << source_entropy(msg_probs) << '\n';
}
