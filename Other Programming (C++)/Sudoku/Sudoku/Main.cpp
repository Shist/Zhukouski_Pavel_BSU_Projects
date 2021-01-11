#include <fstream> // для работы со считыванием из Sudoku.in.txt и выводом в Sudoku.out.txt
#include <iostream> // для того, чтобы выводить сообщения в консоль
#include <vector>
#include <algorithm>
using namespace std; // пространство имен

// Паша, не страдай херью, пожалуйста (с) Глебастер

bool Everything_OK(vector <vector<int>> kletka, int N) // Эта функция проверяет две вещи...
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (kletka[i][j] == 0) // 1) нету ли пустых клеток в получившемся судоку...
				return false;
			for (int k = 0; k < N; k++) // А также 2) то, ... 
			{
				if (j == k)
					continue;
				if (kletka[i][j] == kletka[i][k]) // не повторяются ли числа в строках
					return false;
			}
			for (int k = 0; k < N; k++)
			{
				if (i == k)
					continue;
				if (kletka[i][j] == kletka[k][j]) // и не повторяются ли она в столбцах...
					return false;
			}
		}
	}
	return true; // Тогда и только тогда, судоку будет верным и функция вернет TRUE
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
	int N; // Размерность судоку
	fin >> N; // Считываем здесь размерность судоку... (обычно она равна 9)
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
				chislo[num - 1]--; // Учитываем, сколько и каких цифр в судоку уже есть, а сколько нету...
			}
			ishodnaya_kletka[i][j] = num;
			kletka[i][j] = num;
		}
	}
	vector <int> mas; // В этот массив будем помещать все те цифры, которые не использовались и проходиться по их комбинациям пузырьком
	for (i = N - 1; i >= 0; i--) // Заполняем этот массив недостающими в судоку цифрами (по убыванию)
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
					kletka[i][j] = mas[k]; // вставляем в пустые клетки недостающие цифры текущего сочетания
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
		if (Everything_OK(kletka, N)) // Если все окей, то выводим
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
			Vstavka(ishodnaya_kletka, kletka, N); // Если не получилось, то возвращаем все, как было
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