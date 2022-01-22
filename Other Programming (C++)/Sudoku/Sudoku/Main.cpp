#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int unsolved_count = 81;

bool Everything_OK(vector <vector<int>> kletka, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (kletka[i][j] == 0)
				return false;
			for (int k = 0; k < N; k++) 
			{
				if (j == k)
					continue;
				if (kletka[i][j] == kletka[i][k])
					return false;
			}
			for (int k = 0; k < N; k++)
			{
				if (i == k)
					continue;
				if (kletka[i][j] == kletka[k][j])
					return false;
			}
		}
	}
	return true;
}

bool FieldDecision(vector<vector<int>>& kl, int start_Y, int start_X)
{
	bool something_changed = false;
	for (int num_for_check = 1; num_for_check < 10; num_for_check++)
	{
		vector <vector<char>> field;
		field.resize(3);
		for (int i = 0; i < 3; i++)
			field[i].resize(3);
		int field_unsolved_count = 9;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (kl[start_Y + i][start_X + j] == 0)
					field[i][j] = 'Y';
				else
				{
					field_unsolved_count--;
					field[i][j] = 'N';
				}
		bool skip_num = false;
		for (int i = start_Y; i < start_Y + 3; i++)
			for (int j = start_X; j < start_X + 3; j++)
				if (kl[i][j] == num_for_check)
					skip_num = true;
		if (skip_num)
			continue;
		for (int i = start_Y; i < start_Y + 3; i++)
		{
			for (int j = 0; j < 9; j++)
				if (kl[i][j] == num_for_check)
					for (int f_j = 0; f_j < 3; f_j++)
						if (field[i - start_Y][f_j] != 'N')
						{
							field_unsolved_count--;
							field[i - start_Y][f_j] = 'N';
						}
		}
		for (int j = start_X; j < start_X + 3; j++)
		{
			for (int i = 0; i < 9; i++)
				if (kl[i][j] == num_for_check)
					for (int f_i = 0; f_i < 3; f_i++)
						if (field[f_i][j - start_X] != 'N')
						{
							field_unsolved_count--;
							field[f_i][j - start_X] = 'N';
						}
		}
		if (field_unsolved_count == 1)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					if (field[i][j] == 'Y')
					{
						something_changed = true;
						unsolved_count--;
						kl[start_Y + i][start_X + j] = num_for_check;
					}
	}
	return something_changed;
}

int main()
{
	ifstream fin("Sudoku_in.txt");
	ofstream fout("Sudoku_out.txt");
	int N;
	fin >> N;
	vector <vector<int>> kletka;
	kletka.resize(N);
	int i = 0;
	int j = 0;
	int num = 0;
	for (i = 0; i < N; i++)
	{
		kletka[i].resize(N);
		for (j = 0; j < N; j++)
		{
			fin >> num;
			kletka[i][j] = num;
			if (num != 0)
				unsolved_count--;
		}
	}
	while (true)
	{
		bool nothing_changed = true;
		if (FieldDecision(kletka, 0, 0))
			nothing_changed = false;
		if (FieldDecision(kletka, 0, 3))
			nothing_changed = false;
		if (FieldDecision(kletka, 0, 6))
			nothing_changed = false;
		if (FieldDecision(kletka, 3, 0))
			nothing_changed = false;
		if (FieldDecision(kletka, 3, 3))
			nothing_changed = false;
		if (FieldDecision(kletka, 3, 6))
			nothing_changed = false;
		if (FieldDecision(kletka, 6, 0))
			nothing_changed = false;
		if (FieldDecision(kletka, 6, 3))
			nothing_changed = false;
		if (FieldDecision(kletka, 6, 6))
			nothing_changed = false;
		if (unsolved_count == 0)
		{
			fout << "Success" << endl;
			break;
		}
		if (nothing_changed)
		{
			fout << "Too difficult, decision is imperfect" << endl;
			break;
		}
	}
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			if (j == N - 1)
			{
				if (i != N - 1)
					fout << kletka[i][j] << endl;
				else
					fout << kletka[i][j];
				break;
			}
			fout << kletka[i][j] << " ";
		}
	fin.close();
	fout.close();
	return 0;
}
/*
4 0 3 0 0 2 0 0 0
5 0 0 0 6 0 1 2 0
9 0 0 0 0 0 0 0 4
0 0 8 0 7 0 0 0 0
0 0 0 2 0 3 0 0 8
0 3 6 0 0 0 7 0 0
0 7 0 9 2 0 0 0 0
0 0 0 0 0 5 0 9 6
0 0 0 8 0 4 5 0 0*/
/*
4 6 3 1 8 2 9 7 5
5 8 7 4 6 9 1 2 3
9 2 1 3 5 7 8 6 4
2 4 8 6 7 1 3 5 9
7 5 9 2 4 3 6 1 8
1 3 6 5 9 8 7 4 2
3 7 5 9 2 6 4 8 1
8 1 4 7 3 5 2 9 6
6 9 2 8 1 4 5 3 7*/

/*
0 3 2 0 5 0 1 0 0
0 4 0 6 0 2 0 0 7
1 0 0 7 0 0 5 4 0
0 0 1 0 9 0 0 7 3
8 0 6 0 0 3 2 0 0
0 7 0 8 4 0 0 9 0
3 0 0 9 6 0 0 0 8
0 8 4 0 0 7 0 0 1
5 0 0 0 0 4 7 3 0*/
/*
*/