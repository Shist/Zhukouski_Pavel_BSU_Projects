#include <stdio.h>
#include <stdlib.h>

void Previous_Day(int g, int m, int n)
{
	n--;
	if (n == 0)
	{
		m--;
		if (m == 0)
		{
			g--;
			m = 12;
		}
		if (m % 2 == 0)
		{ // Если месяц четный
			n = 30;
			if (m == 2) // Если февраль
				if (g % 4 == 0) // Проверка года на високосность
					n = 29;
				else
					n = 28;
		}
		else // Если месяц нечетный
			n = 31;
	}
	printf("The date of previous day: %d.%d.%d\n", n, m, g);
}

void Next_Day(int g, int m, int n)
{
	n++;
	if (n == 0)
	{
		m++;
		if (m == 0)
		{
			g++;
			m = 12;
		}
		if (m % 2 == 0)
		{ // Если месяц четный
			n = 30;
			if (m == 2) // Если февраль
				if (g % 4 == 0) // Проверка года на високосность
					n = 29;
				else
					n = 28;
		}
		else // Если месяц нечетный
			n = 31;
	}
	printf("The fate of next day: %d.%d.%d\n", n, m, g);
}

void Days_in_Month(int g, int m)
{
	int result = 0;
	if (m % 2 == 0)
	{ // Месяц четный
		result = 30;
		if (m == 2) // Если февраль
			if (g % 4 == 0) // Если год високосный
				result = 29;
			else
				result = 28;
	}
	else // Месяц нечетный
		result = 31;
	printf("The amount of days in the entered month is %d\n", result);
}

int main(int argc, char* argv[])
{
	int g = atoi(argv[1]);
	int m = atoi(argv[2]);
	int n = atoi(argv[3]);
	printf("Entered date: %d.%d.%d\n", n, m, g);
	Previous_Day(g, m, n);
	Next_Day(g, m, n);
	Days_in_Month(g, m);
	return 0;
}