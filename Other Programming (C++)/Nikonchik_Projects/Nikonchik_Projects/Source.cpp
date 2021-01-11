#include "fraction.h"
#include <iostream>
#include <cmath>
#include "fraction_exception.h"
#pragma warning(disable: 4996)

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	fraction a, b;
	long long num = 0;
	long long den = 1;
	cout << "����� ����������!" << endl;

	while (true)
	{
		try
		{
			cout << "������� ��������� � ����������� ��� ������ �����: " << endl;
			cin >> num >> den;
			a.Setnum(num);
			a.Setden(den);
			break;
		}
		catch (exception & error)
		{
			cout << error.what() << endl << "���������� �����" << endl;
		}
	}

	while (true)
	{
		try
		{
			cout << "������� ��������� � ����������� ��� ������ �����: " << endl;
			cin >> num >> den;
			b.Setnum(num);
			b.Setden(den);
			break;
		}
		catch (exception & error)
		{
			cout << error.what() << endl << "���������� �����" << endl;
		}
	}

	try
	{
		cout << "����� ������: ";
		(a + b).WholeFraction();

		cout << "�������� ������: ";
		(a - b).WholeFraction();

		cout << "������������ ������: ";
		(a * b).WholeFraction();

		cout << "������� ������: ";
		(a / b).WholeFraction();

		cout << "������� ����� ������ �����: ";
		(-a).WholeFraction();

		cout << "������� ����� ������ �����: ";
		(-b).WholeFraction();
	}

	catch (exception & error)
	{
		cout << error.what() << endl;
	}

	cout << "\n*********************************";
	cout << "\n�������� ���������: \n";

	if (a > b)
		cout << a.Getnum() << "/" << a.Getden() << " > " << b.Getnum() << "/" << b.Getden() << endl;

	if (a < b)
		cout << a.Getnum() << "/" << a.Getden() << " < " << b.Getnum() << "/" << b.Getden() << endl;

	if (a == b)
		cout << a.Getnum() << "/" << a.Getden() << " = " << b.Getnum() << "/" << b.Getden() << endl;

	if (a != b)
		cout << a.Getnum() << "/" << a.Getden() << " != " << b.Getnum() << "/" << b.Getden() << endl;

	if (a >= b)
		cout << a.Getnum() << "/" << a.Getden() << " >= " << b.Getnum() << "/" << b.Getden() << endl;

	if (a <= b)
		cout << a.Getnum() << " " << a.Getden() << " <= " << b.Getnum() << " " << b.Getden() << endl;

	cout << "������ ����� (� ���������� ����):";
	a.PrintFraction();
	cout << "������� ����� (� ���������� ����): ";
	b.PrintFraction();

	return 0;
}