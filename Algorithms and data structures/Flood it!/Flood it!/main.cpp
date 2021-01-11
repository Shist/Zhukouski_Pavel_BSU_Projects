#include <fstream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
// ��� ������� ����� ��������� ������� ������ ��� � ������������ ������, ������� �������� � ���� ���� (��� ����� ��� ���������)
void Check_neighbours(vector<vector<pair<int, bool>>> &kletka, queue<pair<int, int>> &kletki_to_capture, int N, int M, int new_color, int i, int j)
{ // ���� � ������� ���� �����, ������� ���� �������� (��� �������), �� ����� ���������, ���� �� � ��� � ������� ������� ������ �� �����, �, ���� ����, �� ��������� �� � �������
	bool check = false; // �������� �� ������� ������������ ������
	if ((i - 1 >= 0) && kletka[i - 1][j].second)
	{ // ���� ������� ������ ���� � ��� ���������, ��...
		kletka[i][j].second = true; // ����������� �������
		check = true;
	}
	else if ((j + 1 < M) && kletka[i][j + 1].second)
	{ // ���� ������ ������ ���� � ��� ���������, ��...
		kletka[i][j].second = true; // ����������� �������
		check = true;
	}
	else if ((i + 1 < N) && kletka[i + 1][j].second)
	{ // ���� ������ ������ ���� � ��� ���������, ��...
		kletka[i][j].second = true; // ����������� �������
		check = true;
	}
	else if ((j - 1 >= 0) && kletka[i][j - 1].second)
	{ // ���� ����� ������ ���� � ��� ���������, ��...
		kletka[i][j].second = true; // ����������� �������
		check = true;
	}
	if (check)
	{ // ���� ������� ������ �������, ��, ���������, ���� �� � ��� ������ � ����� �� ������, ������� ��� �� ���������, � ���� ����, �� ��������� �� � ������� ��� ��������
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
{ // ������ �������� ������ � ����� �� ���������
	queue<pair<int, int>> kletki_to_capture; // � ���� ������� ����� ������� ���������� ��� ������, ������� ��� ����� ������������
	for (deque<pair<int, int>>::iterator it = color[new_color - 1].begin(); it != color[new_color - 1].end(); it++) // ���������� �� ���� ������� ������� ��� �����
		if (!kletka[(*it).first][(*it).second].second) // ���� ������ ��� �� ���������
			Check_neighbours(kletka, kletki_to_capture, N, M, new_color, (*it).first, (*it).second);
	while (!kletki_to_capture.empty())
	{ // ���� ������� �� ���������
		Check_neighbours(kletka, kletki_to_capture, N, M, new_color, kletki_to_capture.front().first, kletki_to_capture.front().second);
		kletki_to_capture.pop();
	}
}

int main()
{
	ifstream fin("floodit.in");
	ofstream fout("floodit.out");
	int N = 0;
	fin >> N; // ���������� �����
	int M = 0;
	fin >> M; // ���������� ��������
	int K = 0;
	fin >> K; // ���������� ������
	vector<deque<pair<int, int>>> color; // ������ �������� � ������������ ������, ���������� � ���� ����
	color.reserve(K); // K ������
	for (int i = 0; i < K; i++)
		color.push_back(deque<pair<int, int>>());
	int T = 0;
	fin >> T; // ���������� ���������� (�����)
	vector<vector<pair<int, bool>>> kletka;
	kletka.reserve(N);
	for (int i = 0; i < N; i++)
	{
		kletka.push_back(vector<pair<int, bool>>());
		kletka[i].reserve(M);
		for (int j = 0; j < M; j++)
		{ // �������� � ���������� ��������� �������
			int temp = 0;
			fin >> temp;
			kletka[i].push_back(make_pair(temp, false));
			color[temp - 1].push_back(make_pair(i, j)); // ������� ���������� ������� � ���� ������ � ��������������� ������
		}
	}
	kletka[0][0].second = true; // ������ � ����� ������� ���� ���������� ����������� ���
	int new_color = kletka[0][0].first;
	Flood_it(kletka, color, N, M, new_color);
	for (int k = 0; k < T; k++)
	{ // ��������� ����
		fin >> new_color; // ����� ����
		Flood_it(kletka, color, N, M, new_color);
	}
	for (int i = 0; i < N; i++)
	{ // �����
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