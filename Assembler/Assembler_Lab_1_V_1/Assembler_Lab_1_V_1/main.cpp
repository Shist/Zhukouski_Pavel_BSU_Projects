#include <iostream>
#include "Fraction.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Дано линейное уравнение: ax + b = 0" << endl;
	long long temp_a = 0;
	long long temp_b = 0;
	int a = 0;
	int b = 0;
	int x = 0;
	int ost = 0;
	try
	{
		cout << "Введите коэффициент a в уравнении: ";
		cin >> temp_a;
		if (temp_a == 0)
			throw exception("Коэффициент a не может быть равен нулю! Иначе это не линейное уравнение!");
		else if (temp_a < INT32_MIN)
			throw exception("Введённый коэффициент a слишком мал!");
		else if (temp_a > INT32_MAX)
			throw exception("Введённый коэффициент a слишком большой!");
		cout << "Введите коэффициент b в уравнении: ";
		cin >> temp_b;
		if (temp_b < INT32_MIN)
			throw exception("Введённый коэффициент b слишком мал!");
		else if (temp_b > INT32_MAX)
			throw exception("Введённый коэффициент b слишком большой!");
	}
	catch (exception &ex)
	{
		cout << "Ошибка при вводе коэффициентов! " << ex.what() << endl;
		return -1;
	}
	a = (int)temp_a;
	b = (int)temp_b;
	cout << "Введённое уравнение: y = " << a << "x + " << b << endl;
	_asm
	{ // Сделать проверку в assembler-е
		mov eax, b // Переносим значение b в область памяти eax
		mov ecx, -1 // Переносим значение -1 в область памяти ecx
		imul ecx // Умножение (в регистре ecx)
		cdq // Расширяет eax до eax : edx и заносит старший бит eax в edx
		idiv a // Деление (в регистре a)
		mov x, eax // Переносим значение eax в переменную x
		mov ost, edx // Переносим значение edx в переменную ost
	}
	Fraction fr(x*a + ost, a);
	cout << "Корень уравнения (в виде дроби): x = " << fr << endl;
	cout << "Корень уравнения (в виде рационального числа): x = " << fr.SeeDouble() << endl;
	return 0;
}