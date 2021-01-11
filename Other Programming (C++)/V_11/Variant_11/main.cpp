#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	setlocale(LC_ALL, ".1251");
	ifstream fin("IN.TXT");
	if (fin.is_open())
	{
		int n;
		if (fin.peek() == EOF)
		{
			cerr << "Файл пуст!";
			return 2;
		}
		fin >> n;
		ofstream fout("OUT.TXT");
		double *arr = new double[n];
		for (int i = 0; i < n; i++)
			fin >> arr[i];
		int maxL = 0, maxR = 0, L, R;
		for (int i = 0; i < n; i++)
		{
			L = R = i;
			while (R < n - 1 && arr[R] < arr[R + 1])
				R++;
			if (R - L > maxR - maxL)
			{
				maxL = L;
				maxR = R;
			}
			i = R;
		}

		for (int i = 0; i < n; i++)
		{
			fout << arr[i] << " ";
		}
		fout << "\n";
		if (maxR - maxL == 0)
			fout << "Последовательность не найдена.";
		else
		{
			for (int i = maxL; i <= maxR; i++)
				fout << arr[i] << " ";
		}
		delete[] arr;
		fin.close();
		fout.close();
	}
	else
	{
		cerr << "Файл не был открыт!\n";
		return 1;
	}
	return 0;
}