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
	cout << "Добро пожаловать!" << endl;

	while (true)
	{
		try
		{
			cout << "Введите числитель и знаменатель для первой дроби: " << endl;
			cin >> num >> den;
			a.Setnum(num);
			a.Setden(den);
			break;
		}
		catch (exception & error)
		{
			cout << error.what() << endl << "Попробуйте снова" << endl;
		}
	}

	while (true)
	{
		try
		{
			cout << "Введите числитель и знаменатель для второй дроби: " << endl;
			cin >> num >> den;
			b.Setnum(num);
			b.Setden(den);
			break;
		}
		catch (exception & error)
		{
			cout << error.what() << endl << "Попробуйте снова" << endl;
		}
	}

	try
	{
		cout << "Сумма дробей: ";
		(a + b).WholeFraction();

		cout << "Разность дробей: ";
		(a - b).WholeFraction();

		cout << "Произведение дробей: ";
		(a * b).WholeFraction();

		cout << "Частное дробей: ";
		(a / b).WholeFraction();

		cout << "Унарный минус первой дроби: ";
		(-a).WholeFraction();

		cout << "Унарный минус второй дробт: ";
		(-b).WholeFraction();
	}

	catch (exception & error)
	{
		cout << error.what() << endl;
	}

	cout << "\n*********************************";
	cout << "\nОперации сравнения: \n";

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

	cout << "Первая дробь (в десятичном виде):";
	a.PrintFraction();
	cout << "Вторная дробь (в десятичном виде): ";
	b.PrintFraction();

	return 0;
}