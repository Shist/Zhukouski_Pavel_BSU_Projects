#include <iostream>
#include <string>
#include <queue>
#include <numeric>

using namespace std;

struct tunstall_node
{
    double prob;
    string msg;
    int msg_len;
};

struct tunstall_node_comparer
{
    bool operator()(const tunstall_node &alpha, const tunstall_node &beta)
        { return alpha.prob < beta.prob; }
};

long long int_pow(long long base, int power)
{
    if (0 == power)
        return 1LL;

    long long result = int_pow(base, power / 2);
    result *= result;
    if (power % 2)
        result *= base;
    return result;
}

vector<tunstall_node> tunstall_algo(
    const vector<double> &source_probs, int code_base, int code_length
)
{
    int source_base = source_probs.size();
    long long splittings = (int_pow(code_base, code_length) - source_base) /
        (source_base - 1);
    vector<tunstall_node> result = { { 1.0, "", 0 } };

    tunstall_node_comparer comparer;
    for (long long i = 0; i <= splittings; ++i) {
        pop_heap(result.begin(), result.end(), comparer);
        tunstall_node node = move(*result.rbegin());
        result.pop_back();

        for (int j = 0; j < source_base; ++j) {
            tunstall_node node_cpy = node;
            node_cpy.prob *= source_probs[j];
            if (0 != node_cpy.msg.size())
                node_cpy.msg += ",";
            node_cpy.msg += to_string(j);
            ++node_cpy.msg_len;
            result.push_back(move(node_cpy));
            push_heap(result.begin(), result.end(), comparer);
        }
    }

    return result;
}

double avg_msg_length(const vector<tunstall_node> &nodes)
{
    return accumulate(
        nodes.begin(), nodes.end(), 0.0,
        [](double result, const tunstall_node &node) {
            return result + node.msg_len * node.prob;
        }
    );
}

double entropy(const vector<double> &probs)
{
    return accumulate(
        probs.begin(), probs.end(), 0.0,
        [](double result, double prob) {
            return result - prob * log2(prob);
        }
    );
}

int main()
{
    int code_base, code_length;
    double curr_prob, total_prob = 0.0;
    vector<double> source_probs;
    cout << "Enter code base and code length:" << endl;
    cin >> code_base >> code_length;
    cout << "Enter probabilities (sum must be 1.0, enter ctrl+D+Enter to end) :" << endl;
    while (cin >> curr_prob) {
        source_probs.push_back(curr_prob);
        total_prob += curr_prob;
        if (total_prob > 1.0)
            cerr << "total probability is " << total_prob << " > 1" << total_prob << endl;
    }
    if (1.0 != total_prob)
        cerr << "the probabilities don't sum up to 1" << endl;
    
    cout << "Generating Tunstall codes...\n";
    vector<tunstall_node> nodes = tunstall_algo(
        source_probs, code_base, code_length
    );
    double avg_src_length = avg_msg_length(nodes);
    cout << "The average message length is " << avg_src_length << '\n';
    cout << "The average code symbols per source message is " <<
        (code_length / avg_src_length) << '\n';
    cout << "The lower bound for the previous average is " <<
        (entropy(source_probs) / log2(code_base)) << '\n';

    return 0;
}
