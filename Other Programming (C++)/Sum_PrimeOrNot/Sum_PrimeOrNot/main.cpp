#include <iostream>
using namespace std;

// �������, ������������, �������� �� ������ ����� �������
bool IsPrime(int num)
{
	if (num == 1 || num == 0)
		return false; // 0 - ������ �� ����������� �����, 1 - �� �������, �� ���������
	for (int i = 2; i * i < num; i++) // ��������� ��� �������� �� ����� �������� �����
		if (num % i == 0) // ���� ���� �� �� ���� �������, �� ����� ���������
			return false;
	return true; // ���� ����� ����, ������ ����� �������
}

int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	cout << "Enter 3 numbers\na = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
	int sum = a + b + c;
	cout << "a + b + c = " << sum << "\n";
	if (IsPrime(sum))
		cout << "The sum of three entered numbers is prime." << endl;
	else
		cout << "The sum of three entered numbers is composite." << endl;
	return 0;
}