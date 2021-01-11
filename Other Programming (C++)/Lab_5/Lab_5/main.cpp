#include <iostream>
#include <cmath> // ���������� ���������� cmath, ����� � ������� ���������� �������������� ������� ������� ���� ��� �������
// ������� 4
using namespace std;

double function1(double x)
{ // ��� ������ �������
	double result = 1.0;
	result = x * atan(x);
	return result;
}

double function2(double x)
{ // ��� ������ �������
	double result = 1.0;
	result = (1.0 / (1.0 + sqrt(x)));
	return result;
}

double function3(double x)
{ // ��� ������� �������
	double result = 1.0;
	result = (2.0 / (1.0 - 4.0 * x));
	return result;
}

double integral(double (*function)(double), double t, double g, double epsilon, int& razb)
{ // ������� ���������� ��������� � �������� ��������� ������� ��������
	razb = 2; // ��� ���������� ����� ���������� ��� ���������� ���������, ������� ������������� 
	double result1 = 10.0, result2 = 0, step;
	while (abs(result2 - result1) >= epsilon) // ���� �� ����������� ��������, ���������� ��������...
	{
		result1 = result2; // � ���������� result1 ������ ������ � ������� (����� ������) ����������
		result2 = 0; // ����������� result2 �������� ����, ����� ���������� ����� (����� ������) ����������
		razb *= 2; // � ������ ��������� �������� ���������� ��������� �����
		step = (g - t) / razb; // � ���������� step (���) ������ �������� �������� ������ ���������, �������� �� ���������� ���������
		for (int i = 0; i < razb; i++)
		{ // ���������� ������� ���� ������������ ����� ��������� �������� � ���� �������
			result2 += (function(t + i * step) + function(t + (i + 1) * step)) / 2 * step;
		} // ��� �������, � ������ ��������� ������� result2 ���������� ��� ����� � ��������� �������� ������� ���������
	}
	return result2; // ���������� �������� �������
}

int main()
{
	int razb1, razb2, razb3; // ����������, �������� ������ � ���, ������� ��������� ������������� ��� ������ �� ���� �������
	double epsilon, int_1, int_2, int_3; // ����������, �������������� �������� ������ � ��������, ������ ���������, ������ ���������, ������� ���������
	const double a1 = 0.0, b1 = 1.7, a2 = 0.0, b2 = 2.0, a3 = -2.0, b3 = -1.2; // ����������, �������� ��������� ��� ����������
	cout << "Enter the desired accuracy of calculations:\n"; // ����� ��������� "������� �������� ��������:"
	cin >> epsilon; // ���� �������� ��������
	if (epsilon < 0.0000001 || epsilon > 0.1)
	{ // ������ �� ������
		cout << "Error. The entered value of epsillon is incorrect or too small.";
		return 1;
	}
	int_1 = integral(function1, a1, b1, epsilon, razb1); // ��������� �������� ������ �������
	int_2 = integral(function2, a2, b2, epsilon, razb2); // ��������� �������� ������ �������
	int_3 = integral(function3, a3, b3, epsilon, razb3); // ��������� �������� ������� �������
	cout.precision(ceil(log10(1/epsilon))); // ������ �������� ��� ������
	cout << "The value of the first calculated integral is:\n" << int_1 << endl; // ����� ������� ���������
	cout << "The number of splits on which the specified accuracy is achieved in the first integral:\n" << razb1 << endl; // ����� ���������� ���������, �������������� ��� ���������� � �������� ��������� ������� ���������
	cout << "The value of the second calculated integral is:\n" << int_2 << endl; // ����� ������� ���������
	cout << "The number of splits on which the specified accuracy is achieved in the second integral:\n" << razb2 << endl; // ����� ���������� ���������, �������������� ��� ���������� � �������� ��������� ������� ���������
	cout << "The value of the third calculated integral is:\n" << int_3 << endl; // ����� �������� ���������
	cout << "The number of splits on which the specified accuracy is achieved in the third integral:\n" << razb3 << endl; // ����� ���������� ���������, �������������� ��� ���������� � �������� ��������� �������� ���������
	return 0;
}