#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <list>
using namespace std;

short int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

bool comp(long long a, long long b)
{
	bool arr_a[10] = { false, false, false, false, false, false, false, false, false, false };
	bool arr_b[10] = { false, false, false, false, false, false, false, false, false, false };
	short int k_a = 0;
	short int k_b = 0;
	long long mod = 10;
	long long del = 1;
	while (a % mod / del != 0)
	{
		for (short int i = 0; i < 10; i++)
		{
			if (a % mod / del == arr[i])
			{
				arr_a[i] = true;
				break;
			}
		}
		mod *= 10;
		del *= 10;
	}
	mod = 10;
	del = 1;
	while (b % mod / del != 0)
	{
		for (short int i = 0; i < 10; i++)
		{
			if (b % mod / del == arr[i])
			{
				arr_b[i] = true;
				break;
			}
		}
		mod *= 10;
		del *= 10;
	}
	for (short int i = 0; i < 10; i++)
	{
		if (arr_a[i])
			k_a++;
		if (arr_b[i])
			k_b++;
	}
	if (k_a > k_b)
		return false;
	else if (k_a < k_b)
		return true;
	else
		return (a < b);
}

bool check = false;

ifstream OpenFile()
{
	ifstream fin("in.txt");
	if (!fin.is_open()) // Проверяем файл на открытие
	{
		throw exception("Input file did not open!");
	}
	if (fin.peek() == EOF) // Проверяем файл на пустоту
	{
		check = true;
		throw exception("File in.txt is empty!");
	}
	return fin;
}

int main()
{
	ifstream fin; // Пробуем открыть входной файл
	try
	{
		fin = OpenFile();
	}
	catch (exception &ex)
	{
		cout << ex.what();
		if (check)
			fin.close();
		return -1;
	}
	list <long long> My_List; // Создаем лист, в который будем вставлять числа из файла in.txt
	long long num;
	while (fin >> num)
	{
		My_List.push_back(num);
	}
	My_List.sort(comp);
	cout << "Our list after sort:" << endl;
	for (auto it = My_List.begin(); it != My_List.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}