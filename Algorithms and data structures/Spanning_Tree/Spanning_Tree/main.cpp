#include <fstream>
#include <vector>
using namespace std;

void Dfs(vector<vector<bool>> G, int N, vector<bool> &edges_used, vector<short int> &result, int curr_edge)
{
	for (int i = 0; i < N; i++)
	{
		if (curr_edge == i) // ���� �� �� ������� ���������, ���������� ��������
			continue;
		if (G[curr_edge][i] && (!edges_used[curr_edge] || !edges_used[i])) // ���� ����� ����� ��������� (i+1) � (j+1) ���������� � ���� �� ���� �� ��� �� �� ���������, �� ...
		{
			result.push_back(curr_edge + 1); // ���������� ������� �����
			edges_used[i] = true; // ��������, ��� �� ������ ������� (i+1)
			result.push_back(i + 1); // ���������� ������� �����
			edges_used[i] = true; // ��������, ��� �� ����� ������ ������� (j+1)
			Dfs(G, N, edges_used, result, i); // � ������ ������ � �������� ����� j
		}
	}
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0; // ����� ������ �����
	fin >> N;

	vector<vector<bool>> G; // ������� ��������� �����
	G.reserve(N);
	vector<bool> edges_used; // ������ � �������� � ���, �������� �� ��� ���� �������, ��� ��� ���
	edges_used.reserve(N);
	edges_used.push_back(true); // �� ����� ������ ������� �� ���������� � ����� ������
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
	vector<short int> result; // � ���� ������� ������ ������� ��� ������ � �����
	int L = 2 * (N - 1);
	result.reserve(L); // ����� ���������� ������ ����� 2*(N - 1)
	Dfs(G, N, edges_used, result, 0); // ����������� ����� � �������
	bool check_connectedness = true; // ������ �� ��������� �����
	for (int i = 0; i < N; i++)
		if (!edges_used[i])
		{ // ���� ���� �� ���� ������� ������������ �� ����, ��...
			check_connectedness = false; // �������, ��� ���� �� ������� �...
			break; // ������� �� �����
		}
	if (check_connectedness)
	{ // ���� ���� �������, ������� ��� ��� �����
		fout << N - 1; // ������� ���������� ���� (��� ������ ����� N - 1)
		for (int i = 1; i < L; i += 2)
		{
			fout << endl;
			fout << result[i - 1] << " " << result[i];
		}
	}
	else // ����� ������� -1
		fout << -1;
	fin.close();
	fout.close();
	return 0;
}