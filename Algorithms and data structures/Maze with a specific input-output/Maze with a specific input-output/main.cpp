#include <fstream>
#include <vector>
using namespace std;

void Rigth_Hand(vector<vector<bool>> &passed, int N, int M, int i, int j, bool &check)
{ // Принцип правой руки
	if (passed[i][j] == 0)
		passed[i][j] = 1;
	else
		check = true;
	if (i == N - 1)
		check = true;
	if (!check && i > 1 && !passed[i - 1][j])
	{ // Если можно, идём наверх
		i--;
		Rigth_Hand(passed, N, M, i, j, check);
		i++;
	}
	if (!check && j < M - 1 && !passed[i][j + 1])
	{ // Если можно, идём вправо
		j++;
		Rigth_Hand(passed, N, M, i, j, check);
		j--;
	}
	if (!check && i < N - 1 && !passed[i + 1][j])
	{ // Если можно, идём вниз
		i++;
		Rigth_Hand(passed, N, M, i, j, check);
		i--;
	}
	if (!check && j > 0 && !passed[i][j - 1])
	{ // Если можно, то идём влево
		j--;
		Rigth_Hand(passed, N, M, i, j, check);
		j++;
	}
	if (!check)
		passed[i][j] = 0;
}

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	int N = 0;
	fin >> N;
	int M = 0;
	fin >> M;
	vector<vector<bool>> passed; // Массив с флажками о том, пройдена ли клетка (если стена, то типо уже пройдена)
	passed.reserve(N);
	for (int i = 0; i < N; i++)
	{
		passed.push_back(vector<bool>());
		passed[i].reserve(M);
		for (int j = 0; j < M; j++)
		{
			char symb = 'c';
			fin >> symb;
			bool temp = 0;
			if (symb == '1')
				temp = 1;
			passed[i].push_back(temp);
		}
	}
	bool check = false;
	for (int j = M - 1; j >= 0; j--)
		if (!passed[0][j])
		{
			passed[0][j] = 1;
			Rigth_Hand(passed, N, M, 1, j, check);
			check = false;
		}
	int in_num = 0;
	int out_num = 0;
	for (int j = 0; j < M; j++)
	{
		if (!passed[0][j])
			in_num++;
		if (!passed[N - 1][j])
			out_num++;
	}
	if (in_num == out_num)
		fout << "Possible";
	else
		fout << "Impossible";
	fin.close();
	fout.close();
	return 0;
}