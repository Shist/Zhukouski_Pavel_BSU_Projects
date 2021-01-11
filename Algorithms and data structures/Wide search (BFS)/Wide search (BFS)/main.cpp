#include <fstream>
#include <vector>
#include <queue>
using namespace std;

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
	queue<int> vertex_queue; // Очередь с вершинами для посещения
	int passed_vertex_count = 0; // Число пройденных вершин
	for (int i = 0; i < N; i++)
		if (!G[i][i])
		{
			vertex_queue.push(i); // Заносим в очередь вершину
			G[i][i] = true; // Помечаем, что она пройдена
			passed_vertex_count++;
			vertex_mark[i] = passed_vertex_count;
			while (!vertex_queue.empty())
			{
				int curr_v = vertex_queue.front(); // Извлекаем первую вершины из очереди
				vertex_queue.pop(); // После чего сразу же удаляем её
				for (int j = 0; j < N; j++)
				{ // Проходимся по всем соседям этой вершины
					if (G[curr_v][j] && !G[j][j])
					{ // Если ребро существует, и вторая вершина посещена еще не была, то...
						vertex_queue.push(j); // Добавляем её в очередь
						G[j][j] = true; // Говорим, что эта вершина уже пройдена
						passed_vertex_count++;
						vertex_mark[j] = passed_vertex_count;
					}
				}
			}
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