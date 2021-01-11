#include <iostream>
using namespace std;

int main()
{
	int N, i, k, p, carry, Num_Digits;
	int Big_Factorial[750]; // ������ ������ � 750 ����������, � ������� �� ������� ����� �� ����� 4 ����, ����� ������� ����� � ������ ��������� 3000 ����, ���� ��������� ������ ��� ������� ���������� 1000! � ������ 
	cout << "Enter number which factorial you want to calculate\n";
	if (!(cin >> N)) // ���������, �� �������� �� ��������� ������� ������� (������ �� ������)
	{
		cout << "Impossible to calculate! The symbols you entered are not numbers!\n";
	}
	else
		if (N < 0 || N > 1000)
	   {
		   cout << "Impossible to calculate factorial correctly! Entered number is negative or it is bigger than 1000\n"; // ������ �� ������ (�� ������������� ����� � �����, ����������� ���������� ����)
	   }
	   else
	   {
		   Num_Digits = 1; // ���������� �������� �����, ������������� �� ����� ������� ����������
		   Big_Factorial[0] = 1; // �������������� ������ ������� ������� 
		   for (i = 2; i <= N; i++) // ��������� ������� ����  (�������� � i = 2, �.�. ��� ������ �������� � i = 1)
		   {
			   carry = 0; // ��������, ����������� ����� � ����� ������ 
			   for (k = 0; k < Num_Digits; k++) // ��������� ���������� ���� 
			   {
				   p = Big_Factorial[k] * i + carry;
				   Big_Factorial[k] = p % 10000; // � ����� �������� ������� ����� ���� �� ������ 4 ����, ����� ������������ ��������� ���� �����, ���������� ���� �������� ����� ��������� 9, ��� �������� � ������������
				   carry = p / 10000; // ������� ��������� ������� ����� � �������� carry, ������� ��������� �� � ����� ������ (����� ������� �������) 
			   }
			   if (carry != 0)
			   {
				   Big_Factorial[k] = carry;
				   Num_Digits++;
			   }
		   }
		   cout << "The factotial of the number " << N << " is ";
		   for (k = Num_Digits - 1; k >= 0; k--)
		   {
			   if (k != Num_Digits - 1) // ���� �� ����� ������� ��������, ��...
				   if (Big_Factorial[k] / 1000 == 0)
					   if (Big_Factorial[k] / 100 == 0)
						   if (Big_Factorial[k] / 10 == 0)
							   cout << "000";
						   else
							   cout << "00";
					   else
						   cout << "0";
			   cout << Big_Factorial[k]; // ������� ������������ �������� ���������� ����� 
		   }
	   }
	   return 0;
}