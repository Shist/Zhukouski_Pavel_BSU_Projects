#include <fstream>
#include <vector>
using namespace std;

void Dfs(vector<vector<bool>> G, int N, vector<bool> &edges_used, vector<short int> &result, int curr_edge)
{
	for (int i = 0; i < N; i++)
	{
		if (curr_edge == i) // Если мы на главное диагонали, пропускаем итерацию
			continue;
		if (G[curr_edge][i] && (!edges_used[curr_edge] || !edges_used[i])) // Если ребро между вершинами (i+1) и (j+1) существует и хотя бы одну из них мы не проходили, то ...
		{
			result.push_back(curr_edge + 1); // Запоминаем вершину ребра
			edges_used[i] = true; // Помечаем, что мы прошли вершину (i+1)
			result.push_back(i + 1); // Запоминаем вершину ребра
			edges_used[i] = true; // Помечаем, что мы также прошли вершину (j+1)
			Dfs(G, N, edges_used, result, i); // И теперь пихаем в рекурсию ребро j
		}
	}
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин графа
	fin >> N;

	vector<vector<bool>> G; // Матрица смежности графа
	G.reserve(N);
	vector<bool> edges_used; // Массив с флажками о том, пройдена та или иная вершина, или еще нет
	edges_used.reserve(N);
	edges_used.push_back(true); // По самой первой вершине мы проходимся в любом случае
	for (int i = 1; i < N; i++)
		edges_used.push_back(false);
	for (int i = 0; i < N; i++)
	{
		G.push_back(vector<bool>());
		G[i].reserve(N);
		for (int j = 0; j < N; j++)
		{
			bool temp = 0;
			fin >> temp;
			G[i].push_back(temp);
		}
	}
	vector<short int> result; // В этом массиве храним вершины для вывода в ответ
	int L = 2 * (N - 1);
	result.reserve(L); // Общее количество вершин равно 2*(N - 1)
	Dfs(G, N, edges_used, result, 0); // Рекурсивный обход в глубину
	bool check_connectedness = true; // Флажок на связность графа
	for (int i = 0; i < N; i++)
		if (!edges_used[i])
		{ // Если хотя бы одна вершина использована не была, то...
			check_connectedness = false; // Говорим, что граф не связный и...
			break; // Выходим из цикла
		}
	if (check_connectedness)
	{ // Если граф связный, выводим все его ребра
		fout << N - 1; // Выводим количество рёбер (оно всегда равно N - 1)
		for (int i = 1; i < L; i += 2)
		{
			fout << endl;
			fout << result[i - 1] << " " << result[i];
		}
	}
	else // Иначе выводим -1
		fout << -1;
	fin.close();
	fout.close();
	return 0;
}