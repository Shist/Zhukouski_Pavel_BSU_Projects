#include "Money.h"
using namespace std;

int main()
{
	try
	{
		int pd;
		int sh;
		double p;
		cout << "Enter the amount of pounds: " << endl;
		cin >> pd;
		cout << "Enter the amount of shillings: " << endl;
		cin >> sh;
		cout << "Enter the amount of pences (accurate to 0.5): " << endl;
		cin >> p;
		Money wallet(pd, sh, p); // �������� ������������
		Money price_of_product(10, 10, 10.0); // ���� ������� ����� ��� ��� �������������� �������������
		cout << "Your balance: " << endl;
		cout << wallet << endl;
		cout << "The result of selling some product: " << endl;
		cout << wallet + price_of_product << endl;  // ��������
		cout << "The result of buying some product: " << endl;
		cout << wallet - price_of_product << endl;  // ���������
		cout << "Your balance with with opposite sign: " << endl;
		wallet = -wallet;  // ����� �����
		cout << wallet << endl;
		wallet = -wallet; // ���������� ������� ��� ���������� �������������...
		Money dobavka(5, 5, 5.0); // ��� �������� ���������� += � -=
		cout << "Your wallet with more 5pd.5sh.5p.:" << endl;
		wallet += dobavka; // �������� �� +=
		cout << wallet << endl;
		wallet -= dobavka; // � �������������� �������� �� -=
		cout << "After moving those 5pd.5sh.5. back from the wallet: " << endl;
		cout << wallet << endl;
		if (price_of_product - dobavka == dobavka) // �������� �� ���������
		{
			cout << "The compare operation works correctly" << endl;
		}
		else
		{
			cout << "The compare operation does not work correctly!!!" << endl;
		}
		Money empty_wallet; // �������� ������������ �� ���������
		cout << "Just some empty wallet: " << endl;
		cout << empty_wallet;
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}