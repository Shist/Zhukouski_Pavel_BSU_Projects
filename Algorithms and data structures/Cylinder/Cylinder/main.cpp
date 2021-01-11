#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int koord_x[4] = { -1, 1, 0, 0 };
int koord_y[4] = { 0, 0 , 1, -1 };

void Check_kletka(vector<vector<char>> &kletka, queue<pair<int, int>> &q, int N, int M, int i, int j)
{ // Функция обработки одной клетки
	for (int k = 0; k < 4; k++)
	{
		int need_j = j + koord_y[k];
		if (need_j < 0 || need_j >= M)
			continue;
		int need_i = (i + koord_x[k] + N) % N;
		if (!kletka[need_i][need_j])
		{
			q.push({ need_i, need_j });
			kletka[need_i][need_j] = 1;
		}
	}
}

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	int N = 0;
	fin >> N;
	int M = 0;
	fin >> M;
	vector<vector<char>> kletka; // Вообще, нам нужен bool, но char тоже подойдёт (он работает быстрее для векторов)
	kletka.reserve(N);
	int temp = 0;
	for (int i = 0; i < N; i++)
	{
		kletka.push_back(vector<char>());
		kletka[i].reserve(M);
		for (int j = 0; j < M; j++)
		{
			fin >> temp;
			kletka[i].push_back(temp);
		}
	}
	int parts_count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			queue<pair<int, int>> q; // Очередь с координатами клеток, которые нужно рассмотреть
			if (!kletka[i][j])
			{ // Если клетка равна нулю, то...
				Check_kletka(kletka, q, N, M, i, j);
				while (!q.empty())
				{ // Пока очередь не пуста...
					int curr_i = q.front().first;
					int curr_j = q.front().second;
					q.pop(); // Удаляем первую пару координат из очереди после того, как записали ее в переменные
					Check_kletka(kletka, q, N, M, curr_i, curr_j); // Проверяем очередную клетку
				}
				parts_count++; // После всех этих операций повышаем счетчик на один (мы сделаем это хотя бы один раз за всю программу)
			}
		}
	fout << parts_count;
	fin.close();
	fout.close();
	return 0;
}