#include <fstream> // ��� ������ �� ����������� �� Sudoku.in.txt � ������� � Sudoku.out.txt
#include <iostream> // ��� ����, ����� �������� ��������� � �������
#include <vector>
#include <algorithm>
using namespace std; // ������������ ����

// ����, �� ������� �����, ���������� (�) ���������

bool Everything_OK(vector <vector<int>> kletka, int N) // ��� ������� ��������� ��� ����...
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (kletka[i][j] == 0) // 1) ���� �� ������ ������ � ������������ ������...
				return false;
			for (int k = 0; k < N; k++) // � ����� 2) ��, ... 
			{
				if (j == k)
					continue;
				if (kletka[i][j] == kletka[i][k]) // �� ����������� �� ����� � �������
					return false;
			}
			for (int k = 0; k < N; k++)
			{
				if (i == k)
					continue;
				if (kletka[i][j] == kletka[k][j]) // � �� ����������� �� ��� � ��������...
					return false;
			}
		}
	}
	return true; // ����� � ������ �����, ������ ����� ������ � ������� ������ TRUE
}

void Vstavka(vector <vector<int>> &ish_kl, vector<vector<int>> &kl, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			kl[i][j] = ish_kl[i][j];
		}
	}
}

int main()
{
	ifstream fin("Sudoku.in.txt");
	ofstream fout("Sudoku.out.txt");
	int N; // ����������� ������
	fin >> N; // ��������� ����� ����������� ������... (������ ��� ����� 9)
	vector <vector<int>> ishodnaya_kletka;
	vector <vector<int>> kletka;
	vector <int> chislo = { 9, 9, 9, 9, 9, 9, 9, 9, 9 };
	ishodnaya_kletka.resize(N);
	kletka.resize(N);
	int i = 0;
	int j = 0;
	int num = 0;
	for (i = 0; i < N; i++)
	{
		ishodnaya_kletka[i].resize(N);
		kletka[i].resize(N);
		for (j = 0; j < N; j++)
		{
			fin >> num;
			if (num != 0)
			{
				chislo[num - 1]--; // ���������, ������� � ����� ���� � ������ ��� ����, � ������� ����...
			}
			ishodnaya_kletka[i][j] = num;
			kletka[i][j] = num;
		}
	}
	vector <int> mas; // � ���� ������ ����� �������� ��� �� �����, ������� �� �������������� � ����������� �� �� ����������� ���������
	for (i = N - 1; i >= 0; i--) // ��������� ���� ������ ������������ � ������ ������� (�� ��������)
	{
		if (chislo[i] != 0)
		{
			mas.push_back(i + 1);
			chislo[i]--;
			i++;
		}
	}
	int check = 0;
	int k = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (kletka[i][j] == 0)
			{
				kletka[i][j] = mas[k];
				k++;
			}
		}
	}
	fout << "The decision of the sudoku is the next:" << endl;
	long long g = 0;
	do
	{
		g++;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (kletka[i][j] == 0)
				{
					kletka[i][j] = mas[k]; // ��������� � ������ ������ ����������� ����� �������� ���������
					k++;
				}
			}
		}
		if (g % 1000000 == 0)
		{
			cout << "###########################################" << endl;
			cout << "Hello, I'm program, and I'M ALIVE YET!!!" << endl;
			cout << "The program is trying to find out correct numbers" << endl;
			cout << "This operation will take at worst (amount of 0 in the sudoku)! of iterations..." << endl;
			cout << "Now, the program has done " << g << " iterations..." << endl;
			cout << "###########################################" << endl;
		}
		if (Everything_OK(kletka, N)) // ���� ��� ����, �� �������
		{
			cout << "THE PROGRAMM HAS FOUNT CORRECT NUMBERS!!! CHECK SUDOKU.OUT.TXT IMMEDIATLY!!!";
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					if (j == N - 1)
					{
						if (i != N - 1)
						{
							fout << kletka[i][j] << endl;
						}
						else
						{
							fout << kletka[i][j];
						}
						break;
					}
					fout << kletka[i][j] << " ";
				}
			}
			goto link;
		}
		else
		{
			Vstavka(ishodnaya_kletka, kletka, N); // ���� �� ����������, �� ���������� ���, ��� ����
			k = 0;
		}
	} while (prev_permutation(mas.begin(), mas.end()));
link:
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