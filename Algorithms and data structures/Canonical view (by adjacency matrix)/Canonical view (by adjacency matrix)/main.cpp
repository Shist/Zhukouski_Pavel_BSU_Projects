#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин
	fin >> N;
	vector<int> P;
	P.reserve(N);
	for (int i = 0; i < N; i++)
		P.push_back(0);
	vector<vector<bool>> G; // Матрица смежности
	G.reserve(N);
	for (int i = 0; i < N; i++)
	{
		G.push_back(vector<bool>());
		G[i].reserve(N);
		for (int j = 0; j < N; j++)
		{
			int temp = 0;
			fin >> temp;
			G[i].push_back(temp);
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (G[i][j])
				P[j] = i + 1;
	for (int i = 0; i < N; i++)
	{
		fout << P[i];
		if (i != N - 1)
			fout << " ";
	}
	fin.close();
	fout.close();
	return 0;
}