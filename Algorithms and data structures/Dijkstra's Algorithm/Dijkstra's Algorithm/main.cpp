#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // ����� ������
	fin >> N;
	int M = 0; // ����� ����
	fin >> M;
	vector<list<pair<int, short int>>> G(N); // ������ ��������� (���� - ��� 1) ������� � 2) ���������� �� �� �� ��������)
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
	vector<long long> min_way(N, INT64_MAX); // ������ � ������������� ������������ �� ������ �� ������
	min_way[0] = 0;
	vector<char> passed(N, 0); // ������ � �������� � ���������� ��������
	using queue_type = priority_queue<pair<long long, int>, std::vector<pair<long long, int>>, std::greater<pair<long long, int>>>;
	queue_type v_queue; // ������������ ������� � ������ (���������� �� �������, ���� �������), ������� ����� ������
	for (int i = 0; i < N; i++)
	{ // ��� ������ �������...
		if (!passed[i])
		{ // ���� ��� ��� �� ��������...
			for (list<pair<int, short int>>::iterator it = G[i].begin(); it != G[i].end(); it++)
			{ // ������� ���� �� �������
				if (min_way[i] + (*it).second < min_way[(*it).first])
					min_way[(*it).first] = min_way[i] + (*it).second; // ���� ���������� ������, ��� ����, �� ���������� ����� (�������)
				v_queue.push(make_pair(min_way[(*it).first], (*it).first)); // ������� ��� ���� (���������� �� �������, ���� �������) � �������
			}
			passed[i] = 1; // �������, ��� ������� ��������
			while (!v_queue.empty())
			{ // ����������� �� ������� ������, � ������� ���������� �������
				int curr_v = v_queue.top().second; // ��������� �� ������� ������ ������� ��� ������������
				v_queue.pop(); // � ������� � �� �������
				if (!passed[curr_v])
				{ // ���� ��� ��� �� ��������...
					for (list<pair<int, short int>>::iterator it = G[curr_v].begin(); it != G[curr_v].end(); it++)
					{ // ������� ���� �� �������
						if (min_way[curr_v] + (*it).second < min_way[(*it).first])
							min_way[(*it).first] = min_way[curr_v] + (*it).second; // ���� ���������� ������, ��� ����, �� ���������� ����� (�������)
						v_queue.push(make_pair(min_way[(*it).first], (*it).first)); // ������� ��� ���� (���������� �� �������, ���� �������) � �������
					}
					passed[curr_v] = true; // �������, ��� ������� ��������
				}
			}
		}
	}
	fout << min_way[N - 1];
	fin.close();
	fout.close();
	return 0;
}