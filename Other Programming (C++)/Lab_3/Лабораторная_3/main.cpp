#include <iostream>
#include <random> 
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	double epsillon, sum = 1, y;
	cout << "������� �������� ����������:\n";
	cin >> epsillon;
	if (epsillon < 0.000001 || epsillon > 1) // ������ �� ������
	{
		cout << "������� ������������ ��� ������� ��������� �������� epsillon" << endl;
		return 0;
	}
	random_device generator;
	uniform_real_distribution<double> distribution(-1, 1);
	double x = distribution(generator), a = x; // ��������� �������� ��������� ����� x �� ���������
	cout << "�� ��������� ������������ ����� R ������ x, ������: " << x << "\n";
	int i = 1;
	while (abs(a) >= epsillon/2) // abs(x) - ������ ����� x
	{
		sum += a;
		a *= x / (i + 1); // �������� ���������� ����� ��������� � ������ ����� ���������
		i++;
	}
	y = abs(sum-exp(x)); // ��������� �������� ������������ ��������
	cout << setprecision(ceil(log10(1 / epsillon))) << "�������� ����� ����� �����: " << exp(x) << endl << // setpresition(...) - ������ ��������, ��������� �� epsillon
	 "�������� ������ ����� �����: " << sum << endl << "����������� ����������: " << y << endl; // exp(x) = e^x
	if (y < epsillon)
	{
		cout << "�������� �������� �����������" << endl;
	}
	else
	{
		cout << "�������� �������� �� �����������" << endl;
	}
	return 0;
}

/* �� ������, ���� ����������� ������ ������ � ����� ��������� � �������:
double k, p;
cout << "������� �����, ��������������� ������ ���������: ";
cin >> k;
cout << "������� �����, ��������������� ����� ���������: ";
cin >> p;
uniform_real_distribution<double> distribution(k, p);
*/