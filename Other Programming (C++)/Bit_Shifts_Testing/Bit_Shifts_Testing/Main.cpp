#include <iostream>

int main()
{
	setlocale(LC_ALL, "Rus");
	int a = 4;
	std::cout << "�������� �����: " << a << std::endl;
	a = a << 1;
	std::cout << "����� ����� ���������� ������ ����� �� ����: " << a;
	return 0;
}