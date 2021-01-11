#include <iostream>
#include <random>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	random_device generator;
	uniform_int_distribution<int> distribution(1, 99);
	int a = distribution(generator);
	int b = distribution(generator);
	int c = distribution(generator);
	cout << "����� ������� � ������� ����� �����: " << a + b << endl;
	cout << "����� ������� � �������� ����� �����: " << b + c << endl;
	cout << "� ����� ������� � �������� ����� �����: " << a + c << endl;
	cout << "������� ��� ��� ����� �� �����������, � � ����� �������� ����� �� ����" << endl;
	cout << "��� �����: ";
	int sum = ((a % 10) + (a / 10) + (b % 10) + (b / 10) + (c % 10) + (c / 10));
	int num = 0;
	while (num != sum)
	{
		cin >> num;
		if (num == sum)
		{
			cout << "���������� �����! ����������, �� �������� � ���� ����!" << endl;
		}
		else
		{
			cout << "�������, ���������� ��� ���: ";
		}
	}
	system("pause");
	return 0;
}