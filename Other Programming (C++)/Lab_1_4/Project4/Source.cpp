#include <iostream> 
using namespace std;

// ��������� �������� ����� ���������� ������������� �����, ��� � ��������� �������: 123456 --> 214365

int main()
{
	cout << "Please, enter any SIX-DIGIT number\n";
	int num, num1, num2, num3, num4, num5, num6;
	cin >> num;
	if (100000 <= num & num <= 999999) // ������ �� ������ 
	{
		num6 = num / 100000; // ��� ���������� ������ ��������� ������� ������� ��������� ��������
		num %= 100000;
		num5 = num / 10000;
		num %= 10000;
		num4 = num / 1000;
		num %= 1000;
		num3 = num / 100;
		num %= 100;
		num2 = num / 10;
		num %= 10;
		num1 = num;
		cout << "The resulting number is the next\n" << num5 << num6 << num3 << num4 << num1 << num2 << endl;
	}
	else
	{
		cout << "Impossible to calculate! The number you entered is not six-digit or it is not a number in general!\n";
	}
	return 0;
}
