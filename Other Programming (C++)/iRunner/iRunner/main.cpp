#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	vector<int> Tree;
	int symbol;
	long long Sum = 0;
	bool check = true;
	while (fin >> symbol)
	{
		Tree.push_back(symbol);
		for (int i = 1; i < Tree.size(); i++)
		{
			if (Tree[i] == symbol)
				check = false;
		}
		if (!check)
			continue;
		Sum += symbol;
		check = true;
	}
	fout << Sum;
	fin.close();
	fout.close();
	return 0;
}