#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m, s;
    fin >> n >> m >> s;

    int buyerTotal = 0; // КОЛИЧЕСТВО монет покупателя
    int sellerTotal = 0; // КОЛИЧЕСТВО моент продавца
    vector<int> allCoins(n + m);

    int coin;
    for (int i = 0; i < n; i++) {
        fin >> coin;
        allCoins[i] = coin;
        buyerTotal += coin;
    }
    for (int i = 0; i < m; i++) {
        fin >> coin;
        allCoins[i + n] = coin;
        sellerTotal += coin;
    }

    if (buyerTotal < s) {
        fout << "No\n";
        return 0;
    }

    int total = buyerTotal + sellerTotal;
    int difference = total - s;
    vector<bool> table(difference + 1);
    table[0] = true;
    for (int i = 0; i < n + m; i++) {
        for (int j = difference - allCoins[i]; j >= 0; j--) {
            if (table[j])
                table[j + allCoins[i]] = true;
        }
    }

    fout << (table[buyerTotal - s] ? "Yes" : "No");

    return 0;
}