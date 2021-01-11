#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // ����� ������
	fin >> N;
	vector<int> vertex_mark; // ������ � ������� ������
	vertex_mark.reserve(N);
	for (int i = 0; i < N; i++)
		vertex_mark.push_back(0);
	vector<vector<bool>> G; // ������� ���������
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
	queue<int> vertex_queue; // ������� � ��������� ��� ���������
	int passed_vertex_count = 0; // ����� ���������� ������
	for (int i = 0; i < N; i++)
		if (!G[i][i])
		{
			vertex_queue.push(i); // ������� � ������� �������
			G[i][i] = true; // ��������, ��� ��� ��������
			passed_vertex_count++;
			vertex_mark[i] = passed_vertex_count;
			while (!vertex_queue.empty())
			{
				int curr_v = vertex_queue.front(); // ��������� ������ ������� �� �������
				vertex_queue.pop(); // ����� ���� ����� �� ������� �
				for (int j = 0; j < N; j++)
				{ // ���������� �� ���� ������� ���� �������
					if (G[curr_v][j] && !G[j][j])
					{ // ���� ����� ����������, � ������ ������� �������� ��� �� ����, ��...
						vertex_queue.push(j); // ��������� � � �������
						G[j][j] = true; // �������, ��� ��� ������� ��� ��������
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