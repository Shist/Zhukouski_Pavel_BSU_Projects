#include <fstream>
#include <vector>
using namespace std;

struct edge
{ // Ребро (дорога)
	int a, b, cost; // a - первый город, b - второй город, cost - стоимость проезда
	bool green_or_not; // green_or_not - зеленая дорога или же красная?
};

void Ford_Bellman(vector<edge> e, vector<int> &d, vector<int> &p, int m, int v, int INF)
{
	d[v] = 0; // Расстояние от начальной вершины до самой себя понятное дело ноль
	while (true)
	{ // Считаем кратчайшие пути из первого города во все остальные
		bool any = false;
		for (int j = 0; j < m; j++)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost)
				{
					d[e[j].b] = d[e[j].a] + e[j].cost;
					p[e[j].b] = e[j].a;
						any = true;
				}
		if (!any)
			break;
	}
}

void Delete_Edges(vector<edge> &e, int &m, int i, int a, int b)
{
	edge item;
	item.a = a; // Город, ИЗ которого мы двигались
	item.b = b; // Город, В который мы приехали
	int min_s = INT32_MAX;
	int need_to_delete = 0; // Тут храним индекс того ребра, которое нужно удалить
	for (int j = 0; j < m; j++) // Проходимся по всем ребрам, что у нас есть...
		if (e[j].a == item.a && e[j].b == item.b && e[j].green_or_not) // Если города совпадают и дорога зеленая, то...
			if (e[j].cost < min_s) // Среди всех таких зеленых дорог (их может быть несколько) мы выбираем минимальную...
			{
				need_to_delete = j;
				min_s = e[j].cost; // Ищем ту дорогу из a в b, который была зеленой и с минимальным путем
			}
	e.erase(e.begin() + need_to_delete); // Удаляем дорогу
	m--; // Уменьшаем m на единицу
}

void Change_Costs(vector<edge> &e, int m, int i, int a, int b)
{ // Функция, меняющая значения ребер, по которым мы проходились на противоположные...
	edge item;
	item.a = a; // Город, ИЗ которого мы двигались
	item.b = b; // Город, В который мы приехали
	int min_s = INT32_MAX;
	int need_to_change = 0; // Тут храним индекс того ребра, которое нужно удалить
	for (int j = 0; j < m; j++) // Проходимся по всем ребрам, что у нас есть...
		if (e[j].a == item.a && e[j].b == item.b && e[j].green_or_not) // Если города совпадают и дорога зеленая, то...
			if (e[j].cost < min_s) // Среди всех таких зеленых дорог (их может быть несколько) мы выбираем минимальную...
			{
				need_to_change = j;
				min_s = e[j].cost; // Ищем ту дорогу из a в b, который была зеленой и с минимальным путем
			}
	e[need_to_change].cost = -e[need_to_change].cost;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n = 0; // n - количество городов
	fin >> n;
	int m = 0; // m - количество дорог
	fin >> m;
	vector<edge> e; // Список рёбер
	const int INF = INT32_MAX; // "Бесконечность"
	e.reserve(m);
	int new_m = 0;
	for (int i = 0; i < m; i++)
	{
		edge temp;
		fin >> temp.a;
		temp.a--;
		fin >> temp.b;
		temp.b--;
		fin >> temp.cost;
		temp.green_or_not = true;
		e.push_back(temp);
		new_m++;
		edge temp_reverse;
		temp_reverse.a = temp.b;
		temp_reverse.b = temp.a;
		temp_reverse.cost = temp.cost;
		temp_reverse.green_or_not = true;
		e.push_back(temp_reverse);
		new_m++;
		edge temp_2;
		temp_2.a = temp.b;
		temp_2.b = temp.a;
		temp_2.green_or_not = false;
		fin >> temp_2.cost;
		if (temp_2.cost != -1)
		{
			temp_2.cost += temp.cost;
			e.push_back(temp_2);
			new_m++;
			edge temp_2_reverse;
			temp_2_reverse.a = temp_2.b;
			temp_2_reverse.b = temp_2.a;
			temp_2_reverse.cost = temp_2.cost;
			temp_2_reverse.green_or_not = false;
			e.push_back(temp_2_reverse);
			new_m++;
		}
	}
	m = new_m;
	vector<int> d(n, INF); // Массив (размера n) расстояний из начальной вершины во все остальные, изначально заполняем все бесконечностями
	vector<int> p(n, -1); // Массив, в котором указан предок для каждой вершины (по умолчанию -1)
	Ford_Bellman(e, d, p, m, 0, INF); // Проходимся Ф-Б в первый раз
	if (d[n - 1] == INF)
		fout << 0;
	else
	{ // Если мы таки добрались до нужного города, то пытаемся вернуться обратно...
		vector<int> path;
		for (int cur = n - 1; cur != -1; cur = p[cur])
			path.push_back(cur);
		for (size_t i = 0; i < path.size() - 1; i++) // Удаляем все ребра, по которым прошлись (по итогу таких должно получиться: path.size() - 1)
		{
			Delete_Edges(e, m, i, path[i + 1], path[i]); // Удаляем все зеленые ребра, по которым мы прошлись с направлением из b в a (ЗЕЛЕНЫЕ a <-- b)
			Change_Costs(e, m, i, path[i], path[i + 1]); // Меняем значения рёбер, по которым прошлись, на противоположные (ЗЕЛЕНЫЕ a --> b)
		}
		vector<int> d_2(n, INF);
		Ford_Bellman(e, d_2, p, m, 0, INF); // Проходимся Ф-Б во второй раз (нам уже не важен массив p, если что)
		if (d_2[n - 1] == INF)
			fout << 0;
		else
			fout << (d[n - 1] + d_2[n - 1]); // Если вернулись, то возвращаем сумму: последний элемент d[] и первый элемент d_2[]
	}
	fin.close();
	fout.close();
	return 0;
}