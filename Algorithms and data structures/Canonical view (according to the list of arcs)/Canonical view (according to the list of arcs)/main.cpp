#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин
	fin >> N;
	vector<int> G;
	G.reserve(N);
	for (int i = 0; i < N; i++)
		G.push_back(0);
	for (int count = 0; count < N - 1; count++)
	{
		int edge_1 = 0;
		fin >> edge_1;
		int edge_2 = 0;
		fin >> edge_2;
		G[edge_2 - 1] = edge_1;
	}
	for (int i = 0; i < N; i++)
	{
		fout << G[i];
		if (i != N - 1)
			fout << " ";
	}
	fin.close();
	fout.close();
	return 0;
}