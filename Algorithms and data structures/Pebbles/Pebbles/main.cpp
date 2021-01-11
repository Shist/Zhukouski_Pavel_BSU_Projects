#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int* Pebbles = new int[n];
	int sum_1 = 0;
	int* answer_1 = new int[n]; // ����� �������� ����� ��������� �������� ����� ��������
	bool free_pebble_1 = false;
	int* answer_2 = new int[n]; // ����� �������� ����� ��������� ������ ����� ��������
	bool free_pebble_2 = false;
	int i = 0;
	for (i; i < n; i++)
	{
		cin >> Pebbles[i];
		if (Pebbles[i] % 2 == 0) // ���� � ����� ����� ������ ����� ��������
		{
			answer_1[i] = 1;
			sum_1++;
			if (free_pebble_2) // ���� ���� ��������� �������
			{
				free_pebble_2 = false;
				answer_2[i] = 2;
			}
			else // ���� ���� ��������� ��������
			{
				free_pebble_2 = true;
				answer_2[i] = 0;
			}
		}
		else // ���� � ����� ����� �������� ����� ��������
		{
			answer_2[i] = 1;
			if (free_pebble_1) // ���� ���� ��������� �������
			{
				free_pebble_1 = false;
				answer_1[i] = 2;
				sum_1 += 2;
			}
			else // ���� ���� ��������� ��������
			{
				free_pebble_1 = true;
				answer_1[i] = 0;
			}
		}
	}
	if (sum_1 == n)
	{ // ���� ������ � ������ ����������� �������� ������, ��...
		for (i = 0; i < n; i++)
			cout << answer_1[i] << " ";
	}
	else
	{ // ���� ������ � �������� ����������� �������� ������, ��...
		for (i = 0; i < n; i++)
			cout << answer_2[i] << " ";
	}
	delete[] Pebbles;
	delete[] answer_1;
	delete[] answer_2;
	return 0;
}