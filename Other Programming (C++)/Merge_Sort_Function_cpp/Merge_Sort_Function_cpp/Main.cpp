#include <iostream>
using namespace std;

void Merge(int* arr, int N, int first, int last)
{ // Функция, сливающая массивы
	int middle, start, final, j;
	int *temp_arr = new int[N];
	middle = (first + last) / 2; // Вычисление среднего элемента
	start = first; // Начало левой части
	final = middle + 1; // Начало правой части
	for (j = first; j <= last; j++) // Выполнять от начала до конца
	{
		if ((start <= middle) && ((final > last) || (arr[start] < arr[final])))
		{
			temp_arr[j] = arr[start];
			start++;
		}
		else
		{
			temp_arr[j] = arr[final];
			final++;
		}
	}
	for (j = first; j <= last; j++)
	{
		arr[j] = temp_arr[j]; // Возвращение результата в список
	}
	delete[]temp_arr;
}

void MergeSort(int* arr, int N, int first, int last)
{ // Рекурсивная процедура сортировки
	if (first < last)
	{
		MergeSort(arr, N, first, (first + last) / 2); // Сортировка левой части
		MergeSort(arr, N, (first + last) / 2 + 1, last); // Сортировка правой части
		Merge(arr, N, first, last); // Слияние двух частей
	}
}

void Arr_Output(int* arr, int N)
{ // Вывод массива
	for (int i = 0; i < N; i++)
	{
		if (i == N - 1)
		{
			cout << arr[i] << ".\n";
			break;
		}
		cout << arr[i] << ", ";
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int arr[] = { 1, 4, 7, 2, 5, 8, 3, 6, 9 };
	int N = sizeof(arr) / sizeof(arr[0]); // Размер массива
	cout << "Исходный массив:\n";
	Arr_Output(arr, N);
	MergeSort(arr, N, 0, N - 1);
	cout << "Исходный массив, упорядоченный сортировкой слиянием:" << endl;
	Arr_Output(arr, N);
	return 0;
}