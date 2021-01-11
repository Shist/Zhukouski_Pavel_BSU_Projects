#include <iostream>
#include <string>
#include <random>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	random_device generator;
	uniform_int_distribution<int> distribution(1, 298);
	cout << "������, ����. ��� ��������� ������� ���� ������� ����� �� 1 �� 298." << endl;
	while (true)
	{
		cout << "����� \"exit\" ��� ������ ��� ������ Enter, ����� ��������� ����� �����.\n";
		string temp;
		getline(cin, temp);
		if (temp == "exit")
			break;
		else
			cout << "��������� ����� - " << distribution(generator) << endl;
	}
	return 0;
}