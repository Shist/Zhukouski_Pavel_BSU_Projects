#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин
	fin >> N;
	int M = 0; // Число рёбер
	fin >> M;
	vector<vector<bool>> G;
	G.reserve(N);
	for (int i = 0; i < N; i++)
	{
		G.push_back(vector<bool>());
		G[i].reserve(N);
		for (int j = 0; j < N; j++)
			G[i].push_back(false);
	}
	int count = 0;
	while (count != M)
	{
		int edge_1 = 0;
		fin >> edge_1;
		int edge_2 = 0;
		fin >> edge_2;
		G[edge_1 - 1][edge_2 - 1] = true;
		G[edge_2 - 1][edge_1 - 1] = true;
		count++;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fout << G[i][j];
			if (j != N - 1)
				fout << " ";
		}
		if (i != N - 1)
			fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}