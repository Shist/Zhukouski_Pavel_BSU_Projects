#include <iostream>
using namespace std;

void Merge(int* arr, int N, int first, int last)
{ // �������, ��������� �������
	int middle, start, final, j;
	int *temp_arr = new int[N];
	middle = (first + last) / 2; // ���������� �������� ��������
	start = first; // ������ ����� �����
	final = middle + 1; // ������ ������ �����
	for (j = first; j <= last; j++) // ��������� �� ������ �� �����
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
		arr[j] = temp_arr[j]; // ����������� ���������� � ������
	}
	delete[]temp_arr;
}

void MergeSort(int* arr, int N, int first, int last)
{ // ����������� ��������� ����������
	if (first < last)
	{
		MergeSort(arr, N, first, (first + last) / 2); // ���������� ����� �����
		MergeSort(arr, N, (first + last) / 2 + 1, last); // ���������� ������ �����
		Merge(arr, N, first, last); // ������� ���� ������
	}
}

void Arr_Output(int* arr, int N)
{ // ����� �������
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
	int N = sizeof(arr) / sizeof(arr[0]); // ������ �������
	cout << "�������� ������:\n";
	Arr_Output(arr, N);
	MergeSort(arr, N, 0, N - 1);
	cout << "�������� ������, ������������� ����������� ��������:" << endl;
	Arr_Output(arr, N);
	return 0;
}