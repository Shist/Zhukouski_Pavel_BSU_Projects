#include <fstream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
// Для каждого цвета требуется хранить список пар с координатами вершин, которые окрашены в этот цвет (это нужно для ускорения)
void Check_neighbours(vector<vector<pair<int, bool>>> &kletka, queue<pair<int, int>> &kletki_to_capture, int N, int M, int new_color, int i, int j)
{ // ЕСЛИ У ВЕРШИНЫ ЕСТЬ СОСЕД, КОТОРЫЙ НАМИ ЗАХВАЧЕН (ОНА УДАЧНАЯ), ТО ТОГДА ПРОВЕРЯЕМ, ЕСТЬ ЛИ У НЕЕ В СОСЕДЯХ ВЕРШИНЫ ТАКОГО ЖЕ ЦВЕТА, И, ЕСЛИ ЕСТЬ, ТО ДОБАВЛЯЕМ ИХ В ОЧЕРЕДЬ
	bool check = false; // Проверка на наличие захваченного соседа
	if ((i - 1 >= 0) && kletka[i - 1][j].second)
	{ // Если верхняя клетка есть и она захвачена, то...
		kletka[i][j].second = true; // Захватываем текущую
		check = true;
	}
	else if ((j + 1 < M) && kletka[i][j + 1].second)
	{ // Если правая клетка есть и она захвачена, то...
		kletka[i][j].second = true; // Захватываем текущую
		check = true;
	}
	else if ((i + 1 < N) && kletka[i + 1][j].second)
	{ // Если нижняя клетка есть и она захвачена, то...
		kletka[i][j].second = true; // Захватываем текущую
		check = true;
	}
	else if ((j - 1 >= 0) && kletka[i][j - 1].second)
	{ // Если левая клетка есть и она захвачена, то...
		kletka[i][j].second = true; // Захватываем текущую
		check = true;
	}
	if (check)
	{ // Если текущая клетка удачная, то, проверяем, есть ли у нее соседи с таким же цветом, которые еще не захвачены, и если есть, то добавляем их в очередь для проверки
		if ((i - 1 >= 0) && !kletka[i - 1][j].second && kletka[i - 1][j].first == new_color)
			kletki_to_capture.push(make_pair(i - 1, j));
		if ((j + 1 < M) && !kletka[i][j + 1].second && kletka[i][j + 1].first == new_color)
			kletki_to_capture.push(make_pair(i, j + 1));
		if ((i + 1 < N) && !kletka[i + 1][j].second && kletka[i + 1][j].first == new_color)
			kletki_to_capture.push(make_pair(i + 1, j));
		if ((j - 1 >= 0) && !kletka[i][j - 1].second && kletka[i][j - 1].first == new_color)
			kletki_to_capture.push(make_pair(i, j - 1));
	}
}

void Flood_it(vector<vector<pair<int, bool>>> &kletka, vector<deque<pair<int, int>>> &color, int N, int M, int new_color)
{ // Захват соседних клеток с таким же значением
	queue<pair<int, int>> kletki_to_capture; // В этой очереди будем хранить координаты тех клеток, которые еще нужно пересмотреть
	for (deque<pair<int, int>>::iterator it = color[new_color - 1].begin(); it != color[new_color - 1].end(); it++) // Проходимся по всем клеткам нужного нам цвета
		if (!kletka[(*it).first][(*it).second].second) // Если клетка еще не захвачена
			Check_neighbours(kletka, kletki_to_capture, N, M, new_color, (*it).first, (*it).second);
	while (!kletki_to_capture.empty())
	{ // Пока очередь не очистится
		Check_neighbours(kletka, kletki_to_capture, N, M, new_color, kletki_to_capture.front().first, kletki_to_capture.front().second);
		kletki_to_capture.pop();
	}
}

int main()
{
	ifstream fin("floodit.in");
	ofstream fout("floodit.out");
	int N = 0;
	fin >> N; // Количество строк
	int M = 0;
	fin >> M; // Количество столбцов
	int K = 0;
	fin >> K; // Количество цветов
	vector<deque<pair<int, int>>> color; // Массив очередей с координатами вершин, окрашенных в этот цвет
	color.reserve(K); // K цветов
	for (int i = 0; i < K; i++)
		color.push_back(deque<pair<int, int>>());
	int T = 0;
	fin >> T; // Количество перекрасок (ходов)
	vector<vector<pair<int, bool>>> kletka;
	kletka.reserve(N);
	for (int i = 0; i < N; i++)
	{
		kletka.push_back(vector<pair<int, bool>>());
		kletka[i].reserve(M);
		for (int j = 0; j < M; j++)
		{ // Создание и заполнение элементов цветами
			int temp = 0;
			fin >> temp;
			kletka[i].push_back(make_pair(temp, false));
			color[temp - 1].push_back(make_pair(i, j)); // Заносим координаты вершины с этим цветом в соответствующий список
		}
	}
	kletka[0][0].second = true; // Клетка в левом верхнем углу изначально принадлежит нам
	int new_color = kletka[0][0].first;
	Flood_it(kletka, color, N, M, new_color);
	for (int k = 0; k < T; k++)
	{ // Совершаем ходы
		fin >> new_color; // Новый цвет
		Flood_it(kletka, color, N, M, new_color);
	}
	for (int i = 0; i < N; i++)
	{ // Вывод
		for (int j = 0; j < M; j++)
		{
			if (kletka[i][j].second)
				fout << new_color;
			else
				fout << kletka[i][j].first;
			if (j != M - 1)
				fout << " ";
		}
		if (i != N - 1)
			fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}