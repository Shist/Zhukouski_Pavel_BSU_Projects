#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct msg_node
{
    int num;
    string code;
};

struct huffman_node
{
    double node_prob;
    list<msg_node> msgs;
};

struct huffman_node_cmp
{
    bool operator()(const huffman_node &a, const huffman_node &b)
        { return a.node_prob > b.node_prob; }
};

huffman_node merge_huffman_nodes(huffman_node &a, huffman_node &b)
{
    huffman_node result { a.node_prob + b.node_prob };
    for (auto &msg : a.msgs)
        msg.code = '0' + msg.code;
    for (auto &msg : b.msgs)
        msg.code = '1' + msg.code;
    result.msgs = move(a.msgs);
    result.msgs.splice(result.msgs.begin(), b.msgs);
    return result;
}

vector<string> huffman_construct(const vector<double> &msg_probs)
{
    priority_queue<huffman_node, vector<huffman_node>, 
        huffman_node_cmp> node_heap;
    for (int i = 0; i < msg_probs.size(); ++i) {
        msg_node msg { i };
        huffman_node leaf { msg_probs[i] };
        leaf.msgs.push_back(move(msg));
        node_heap.push(move(leaf));
    }
    
    while (node_heap.size() > 1) {
        huffman_node first = node_heap.top();
        node_heap.pop();
        huffman_node second = node_heap.top();
        node_heap.pop();
        node_heap.push(merge_huffman_nodes(first, second));
    }

    huffman_node root = node_heap.top();
    vector<string> result(msg_probs.size());
    for (auto &msg : root.msgs)
        result[msg.num] = move(msg.code);

    return result;
}

int number_of_digits(int num)
{
    int result = 0;
    do {
        ++result; 
        num /= 10;
    } while (num > 0);
    return result;
}

double average_length(
    const vector<string> &huffman_codes, 
    const vector<double> &msg_probs
)
{
    double result = 0;
    for (int i = 0; i < huffman_codes.size(); ++i)
        result += huffman_codes[i].length() * msg_probs[i];
    return result;
}

double source_entropy(const vector<double> &msg_probs)
{
    double result = 0;
    for (int i = 0; i < msg_probs.size(); ++i)
        result += -msg_probs[i] * log2(msg_probs[i]);
    return result;
}

int main()
{
    vector<double> msg_probs;
    double curr_prob, total_prob = 0;
    cout << "Enter probabilities (sum must be 1.0, enter ctrl+D+Enter to end) :" << endl;
    while (cin >> curr_prob) {
        msg_probs.push_back(curr_prob);
        total_prob += curr_prob;
        if (total_prob > 1.0) {
            cerr << "total probability is " << total_prob << " > 1" << endl;
            return 1;
        }
    }
    if (1.0 != total_prob) {
        cerr << "the probabilities don't sum up to 1" << endl;
        return 1;
    }

    auto huffman_codes = huffman_construct(msg_probs);
    cout << "The Huffman codes for the messages are as follows:\n";
    int places = number_of_digits(msg_probs.size());
    for (int i = 0; i < huffman_codes.size(); ++i)
        cout << setw(places) << i << " | " << huffman_codes[i] << '\n';

    cout << "The average length of the code is " 
        << average_length(huffman_codes, msg_probs) << '\n';
    cout << "The entropy of the source is "
        << source_entropy(msg_probs) << '\n';
}
