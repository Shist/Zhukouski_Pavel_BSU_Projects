#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // Число вершин
	fin >> N;
	int M = 0; // Число рёбер
	fin >> M;
	vector<list<pair<int, short int>>> G(N); // Список смежности (пара - это 1) вершина и 2) расстояние до неё от исходной)
	for (int i = 0; i < N; i++)
		G.push_back(list<pair<int, short int>>());
	int count = 0;
	while (count != M)
	{
		int v_1 = 0;
		fin >> v_1;
		int v_2 = 0;
		fin >> v_2;
		short int L = 0;
		fin >> L;
		G[v_1 - 1].push_back(make_pair(v_2 - 1, L));
		G[v_2 - 1].push_back(make_pair(v_1 - 1, L));
		count++;
	}
	vector<long long> min_way(N, INT64_MAX); // Массив с минимальнымии расстояниями до вершин из первой
	min_way[0] = 0;
	vector<char> passed(N, 0); // Массив с флажками о посещенных вершинах
	using queue_type = priority_queue<pair<long long, int>, std::vector<pair<long long, int>>, std::greater<pair<long long, int>>>;
	queue_type v_queue; // Приоритетная очередь с парами (расстояние до вершины, сама вершина), которые нужно пройти
	for (int i = 0; i < N; i++)
	{ // Для каждой вершины...
		if (!passed[i])
		{ // Если она еще не посещена...
			for (list<pair<int, short int>>::iterator it = G[i].begin(); it != G[i].end(); it++)
			{ // Смотрим всех ее соседей
				if (min_way[i] + (*it).second < min_way[(*it).first])
					min_way[(*it).first] = min_way[i] + (*it).second; // Если расстояние меньше, чем было, то запоминаем новое (меньшее)
				v_queue.push(make_pair(min_way[(*it).first], (*it).first)); // Заносим эту пару (расстояние до вершины, сама вершина) в очередь
			}
			passed[i] = 1; // Говорим, что вершина посещена
			while (!v_queue.empty())
			{ // Пробегаемся по очереди вершин, в которой накопились вершины
				int curr_v = v_queue.top().second; // Извлекаем из очереди первую вершину для рассмотрения
				v_queue.pop(); // И удаляем её из очереди
				if (!passed[curr_v])
				{ // Если она еще не посещена...
					for (list<pair<int, short int>>::iterator it = G[curr_v].begin(); it != G[curr_v].end(); it++)
					{ // Смотрим всех ее соседей
						if (min_way[curr_v] + (*it).second < min_way[(*it).first])
							min_way[(*it).first] = min_way[curr_v] + (*it).second; // Если расстояние меньше, чем было, то запоминаем новое (меньшее)
						v_queue.push(make_pair(min_way[(*it).first], (*it).first)); // Заносим эту пару (расстояние до вершины, сама вершина) в очередь
					}
					passed[curr_v] = true; // Говорим, что вершина посещена
				}
			}
		}
	}
	fout << min_way[N - 1];
	fin.close();
	fout.close();
	return 0;
}