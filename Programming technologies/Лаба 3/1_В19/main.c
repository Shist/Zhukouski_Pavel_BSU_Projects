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
		if (m == 4 || m == 6 || m == 9 || m == 11) // ������, ����, ��������, ������ - 30 ����
			n = 30;
		else if (m == 2) // ������� - 28/29 ����
		{
			if (g % 4 == 0) // �������� ���� �� ������������
				n = 29;
			else
				n = 28;
		}
		else // ��������� ������ - 31 ����
			n = 31;
	}
	printf("The date of previous day: %d.%d.%d\n", n, m, g);
}

void Next_Day(int g, int m, int n)
{
	n++;
	if (m == 4 || m == 6 || m == 9 || m == 11) // ������, ����, ��������, ������ - 30 ����
	{
		if (n == 31)
		{
			m++;
			n = 1;
		}
	}
	else if (m == 2) // ������� - 28/29 ����
	{
		if (g % 4 == 0) // �������� ���� �� ������������
		{
			if (n == 30)
			{
				m++;
				n = 1;
			}
		}
		else
		{
			if (n == 29)
			{
				m++;
				n = 1;
			}
		}
	}
	else // ��������� ������ - 31 ����
	{
		if (n == 32)
		{
			m++;
			n = 1;
		}
	}
	if (m == 13)
	{
		m = 1;
		g++;
	}
	printf("The date of next day: %d.%d.%d\n", n, m, g);
}

void Days_in_Month(int g, int m)
{
	int result = 0;
	if (m % 2 == 0)
	{ // ����� ������
		result = 30;
		if (m == 2) // ���� �������
			if (g % 4 == 0) // ���� ��� ����������
				result = 29;
			else
				result = 28;
	}
	else // ����� ��������
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