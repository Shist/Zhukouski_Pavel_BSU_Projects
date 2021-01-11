#include <iostream> 
using namespace std;

/* ������� ��� ������� ��� */
int gcd(int num1, int num2)
{
	while (num2 != 0)
	{
		num1 %= num2;
		swap(num1, num2);
	}

	return(num1);
}
/* ������� ��� ������� ��� */

int main()
{
	cout << "Enter two natural numbers for which you want to calculate the least common multiple and the greatest common divisor\n";
	int num1, num2, gcdNum;
	if (!(cin >> num1 >> num2)) // ���������, �� �������� �� ��������� ������� ������� (������ �� ������)
	{
		cout << "Impossible to calculate! The symbols you entered are not numbers!\n";
	}
	else
	{
		gcdNum = gcd(num1, num2); // ������� �������� ��� 
		cout << "The greatest common divisor is \n";
		cout << gcdNum << endl;
		cout << "The least common multiple is \n";
		cout << num1 * num2 / gcdNum << endl; // ����������� � ������� ��� ����� ��� ��������� ��� 
	}
	return 0;
}