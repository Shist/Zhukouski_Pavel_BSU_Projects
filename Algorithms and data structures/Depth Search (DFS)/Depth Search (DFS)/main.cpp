#include <fstream>
#include <vector>
using namespace std;

void Dfs(vector<vector<bool>> &G, int N, vector<int> &vertex_mark, int curr_v, int &passed_vertex_count)
{ // DFS (рекурсия)
	for (int i = 0; i < N; i++)
		if (G[curr_v][i] && !G[i][i])
		{
			G[i][i] = true;
			passed_vertex_count++;
			vertex_mark[i] = passed_vertex_count;
			Dfs(G, N, vertex_mark, i, passed_vertex_count);
		}
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин
	fin >> N;
	vector<int> vertex_mark; // Массив с метками вершин
	vertex_mark.reserve(N);
	for (int i = 0; i < N; i++)
		vertex_mark.push_back(0);
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
	int passed_vertex_count = 0; // Число пройденных вершин
	for (int i = 0; i < N; i++)
		if (!G[i][i])
		{ // Рекурсивно ищем в глубину
			G[i][i] = true;
			passed_vertex_count++;
			vertex_mark[i] = passed_vertex_count;
			Dfs(G, N, vertex_mark, i, passed_vertex_count);
		}
	for (int i = 0; i < N; i++)
	{
		fout << vertex_mark[i];
		if (i != N - 1)
			fout << " ";
	}
	fin.close();
	fout.close();
	return 0;
}