#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int* Pebbles = new int[n];
	int sum_1 = 0;
	int* answer_1 = new int[n]; // Будем пытаться везде оставлять нечётное число камешков
	bool free_pebble_1 = false;
	int* answer_2 = new int[n]; // Будем пытаться везде оставлять чётное число камешков
	bool free_pebble_2 = false;
	int i = 0;
	for (i; i < n; i++)
	{
		cin >> Pebbles[i];
		if (Pebbles[i] % 2 == 0) // Если в ящике лежит чётное число камешков
		{
			answer_1[i] = 1;
			sum_1++;
			if (free_pebble_2) // Если есть свободный камешек
			{
				free_pebble_2 = false;
				answer_2[i] = 2;
			}
			else // Если нету свободных камешков
			{
				free_pebble_2 = true;
				answer_2[i] = 0;
			}
		}
		else // Если в ящике лежит нечётное число камешков
		{
			answer_2[i] = 1;
			if (free_pebble_1) // Если есть свободный камешек
			{
				free_pebble_1 = false;
				answer_1[i] = 2;
				sum_1 += 2;
			}
			else // Если нету свободных камешков
			{
				free_pebble_1 = true;
				answer_1[i] = 0;
			}
		}
	}
	if (sum_1 == n)
	{ // Если ящиков с чётным количеством камешков больше, то...
		for (i = 0; i < n; i++)
			cout << answer_1[i] << " ";
	}
	else
	{ // Если ящиков с нечётным количеством камешков больше, то...
		for (i = 0; i < n; i++)
			cout << answer_2[i] << " ";
	}
	delete[] Pebbles;
	delete[] answer_1;
	delete[] answer_2;
	return 0;
}