#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool comp(pair<vector<int>, vector<int>> a, pair<vector<int>, vector<int>> b)
{
	return ((a.first.size() > a.second.size()) ? a.first.size() : a.second.size()) > ((b.first.size() > b.second.size()) ? b.first.size() : b.second.size());
}

int main()
{
	ifstream fin("input.in");
	ofstream fout("output.out");
	int N = 0;
	fin >> N; // ����� ������
	vector<vector<int>> G; // ����
	G.reserve(N);
	int temp = 0;
	for (int i = 0; i < N; i++)
	{
		G.push_back(vector<int>());
		G[i].reserve(N);
		for (int j = 0; j < N; j++)
		{
			fin >> temp;
			if (i == j)
				G[i].push_back(temp);
			else // ���������� �������� �������� (����� ����, ���� �� ����� ���� �����)
				G[i].push_back(!temp);
		}
	}
	queue<int> vertex_queue; // ������� � ��������� ��� ���������
	bool check_bipart = true; // ������ �� ��, �������� �� ���� ����������
	vector<pair<vector<int>, vector<int>>> compon_weight; // ������ ��� �������� - ���������� ����� ������ ��� ������ ��������� ���������
	compon_weight.reserve(N); // � ������ ������ - N ��������� ��������� (N ������������� ������)
	for (int i = 0; i < N && check_bipart; i++)
		if (G[i][i] == 0) // ���� �� �����, ������, �� ���������� �� ����� ���������� ���������
		{ // ���� ������� �� ���� ��������, ��...
			vector<int> first_team;
			first_team.reserve(N); // � ������ ������ - N ������ � ����� �� ������
			vector<int> second_team;
			second_team.reserve(N); // � ������ ������ - N ������ � ����� �� ������
			vertex_queue.push(i); // ������� � ������� �������
			G[i][i] = 1; // ��������, ��� ��� �������� � ��������� � ������ ����
			first_team.push_back(i);
			while (!vertex_queue.empty() && check_bipart)
			{
				int curr_v = vertex_queue.front(); // ��������� ������ ������� �� �������
				vertex_queue.pop(); // ����� ���� ����� �� ������� �
				for (int j = 0; j < N && check_bipart; j++)
				{ // ���������� �� ���� ������� ���� �������
					if (G[j][j] == 0)
					{ // ���� ������� j �� ���� ��������, ��...
						if (G[curr_v][j])
						{ // ���� ����� [curr_v, j] ���� � �����, ��...
							vertex_queue.push(j); // ��������� � � �������
							if (3 - G[curr_v][curr_v] == 2)
							{
								G[j][j] = 2; // �������, ��� ��� ������� ��� �������� � ��������� �� ������ ����
								second_team.push_back(j);
							}
							else
							{
								G[j][j] = 1; // �������, ��� ��� ������� ��� �������� � ��������� � ������ ����
								first_team.push_back(j);
							}
						}
					}
					else if (G[curr_v][curr_v] == G[j][j] && G[curr_v][j] && curr_v != j)
					{ // ��������� ������������ (������� �����)
						check_bipart = false;
						break;
					}
				}
			}
			compon_weight.push_back(make_pair(first_team, second_team)); // ��������� � ��������� ����� ����� ������ � ���������� ���������� ���������
		}
	if (!check_bipart)
	{
		fout << "NO";
		return 0;
	}
	sort(compon_weight.begin(), compon_weight.end(), comp); // ��������� ���� ����� � ������ ����������
	vector<int> versh_in_first_team;
	versh_in_first_team.reserve(N);
	vector<int> versh_in_second_team;
	versh_in_second_team.reserve(N);
	int first_team_sum = compon_weight[0].first.size();
	for (int i = 0; i < compon_weight[0].first.size(); i++)
		versh_in_first_team.push_back(compon_weight[0].first[i]);
	int second_team_sum = compon_weight[0].second.size();
	for (int i = 0; i < compon_weight[0].second.size(); i++)
		versh_in_second_team.push_back(compon_weight[0].second[i]);
	for (int i = 1; i < compon_weight.size(); i++)
	{
		int pobolshe = 0;
		int pomenshe = 0;
		bool first_comp_w_is_bigger = false;
		if (compon_weight[i].first.size() > compon_weight[i].second.size())
		{
			pobolshe = compon_weight[i].first.size();
			pomenshe = compon_weight[i].second.size();
			first_comp_w_is_bigger = true;
		}
		else
		{
			pobolshe = compon_weight[i].second.size();
			pomenshe = compon_weight[i].first.size();
		}
		if (first_team_sum > second_team_sum)
		{
			first_team_sum += pomenshe;
			second_team_sum += pobolshe;
			if (first_comp_w_is_bigger)
			{
				for (int j = 0; j < compon_weight[i].first.size(); j++)
					versh_in_second_team.push_back(compon_weight[i].first[j]);
				for (int j = 0; j < compon_weight[i].second.size(); j++)
					versh_in_first_team.push_back(compon_weight[i].second[j]);
			}
			else
			{
				for (int j = 0; j < compon_weight[i].first.size(); j++)
					versh_in_first_team.push_back(compon_weight[i].first[j]);
				for (int j = 0; j < compon_weight[i].second.size(); j++)
					versh_in_second_team.push_back(compon_weight[i].second[j]);
			}
		}
		else
		{
			first_team_sum += pobolshe;
			second_team_sum += pomenshe;
			if (first_comp_w_is_bigger)
			{
				for (int j = 0; j < compon_weight[i].first.size(); j++)
					versh_in_first_team.push_back(compon_weight[i].first[j]);
				for (int j = 0; j < compon_weight[i].second.size(); j++)
					versh_in_second_team.push_back(compon_weight[i].second[j]);
			}
			else
			{
				for (int j = 0; j < compon_weight[i].first.size(); j++)
					versh_in_second_team.push_back(compon_weight[i].first[j]);
				for (int j = 0; j < compon_weight[i].second.size(); j++)
					versh_in_first_team.push_back(compon_weight[i].second[j]);
			}
		}
	}
	bool sums_check = true;
	bool first_is_bigger_or_not = true;
	if ((first_team_sum > 2 * second_team_sum) || (second_team_sum > 2 * first_team_sum))
		sums_check = false;
	if (first_team_sum < second_team_sum)
		first_is_bigger_or_not = false;
	if (sums_check)
	{
		fout << "YES" << endl;
		int count = 0;
		if (first_is_bigger_or_not)
		{
			sort(versh_in_first_team.begin(), versh_in_first_team.end());
			for (int i = 0; i < versh_in_first_team.size(); i++)
			{
				fout << (versh_in_first_team[i] + 1);
				if (i != versh_in_first_team.size() - 1)
					fout << " ";
			}
		}
		else
		{
			sort(versh_in_second_team.begin(), versh_in_second_team.end());
			for (int i = 0; i < versh_in_second_team.size(); i++)
			{
				fout << (versh_in_second_team[i] + 1);
				if (i != versh_in_second_team.size() - 1)
					fout << " ";
			}
		}
	}
	else
		fout << "NO";
	fin.close();
	fout.close();
	return 0;
}