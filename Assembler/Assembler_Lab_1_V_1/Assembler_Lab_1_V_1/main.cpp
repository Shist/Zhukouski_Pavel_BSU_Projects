#include <iostream>
#include "Fraction.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "���� �������� ���������: ax + b = 0" << endl;
	long long temp_a = 0;
	long long temp_b = 0;
	int a = 0;
	int b = 0;
	int x = 0;
	int ost = 0;
	try
	{
		cout << "������� ����������� a � ���������: ";
		cin >> temp_a;
		if (temp_a == 0)
			throw exception("����������� a �� ����� ���� ����� ����! ����� ��� �� �������� ���������!");
		else if (temp_a < INT32_MIN)
			throw exception("�������� ����������� a ������� ���!");
		else if (temp_a > INT32_MAX)
			throw exception("�������� ����������� a ������� �������!");
		cout << "������� ����������� b � ���������: ";
		cin >> temp_b;
		if (temp_b < INT32_MIN)
			throw exception("�������� ����������� b ������� ���!");
		else if (temp_b > INT32_MAX)
			throw exception("�������� ����������� b ������� �������!");
	}
	catch (exception &ex)
	{
		cout << "������ ��� ����� �������������! " << ex.what() << endl;
		return -1;
	}
	a = (int)temp_a;
	b = (int)temp_b;
	cout << "�������� ���������: y = " << a << "x + " << b << endl;
	_asm
	{ // ������� �������� � assembler-�
		mov eax, b // ��������� �������� b � ������� ������ eax
		mov ecx, -1 // ��������� �������� -1 � ������� ������ ecx
		imul ecx // ��������� (� �������� ecx)
		cdq // ��������� eax �� eax : edx � ������� ������� ��� eax � edx
		idiv a // ������� (� �������� a)
		mov x, eax // ��������� �������� eax � ���������� x
		mov ost, edx // ��������� �������� edx � ���������� ost
	}
	Fraction fr(x*a + ost, a);
	cout << "������ ��������� (� ���� �����): x = " << fr << endl;
	cout << "������ ��������� (� ���� ������������� �����): x = " << fr.SeeDouble() << endl;
	return 0;
}