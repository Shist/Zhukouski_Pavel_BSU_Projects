#include <fstream>
#include <vector>
#include <list>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин
	fin >> N;
	int M = 0; // Число рёбер
	fin >> M;
	vector<list<int>> G;
	for (int i = 0; i < N; i++)
		G.push_back(list<int>());
	int count = 0;
	while (count != M)
	{
		int edge_1 = 0;
		fin >> edge_1;
		int edge_2 = 0;
		fin >> edge_2;
		G[edge_1 - 1].push_back(edge_2);
		G[edge_2 - 1].push_back(edge_1);
		count++;
	}
	for (int i = 0; i < N; i++)
	{
		fout << G[i].size();
		if (!G[i].empty())
		{
			list<int>::iterator it;
			for (it = G[i].begin(); it != G[i].end(); it++)
			{
				fout << " ";
				fout << (*it);
			}
		}
		if (i != N - 1)
			fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}