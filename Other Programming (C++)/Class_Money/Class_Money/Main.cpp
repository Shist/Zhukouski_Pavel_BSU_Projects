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
		Money wallet(pd, sh, p); // Проверка конструктора
		Money price_of_product(10, 10, 10.0); // Этот кошелек нужен нам для арифметических экспериментов
		cout << "Your balance: " << endl;
		cout << wallet << endl;
		cout << "The result of selling some product: " << endl;
		cout << wallet + price_of_product << endl;  // Сложение
		cout << "The result of buying some product: " << endl;
		cout << wallet - price_of_product << endl;  // Вычитание
		cout << "Your balance with with opposite sign: " << endl;
		wallet = -wallet;  // Смена знака
		cout << wallet << endl;
		wallet = -wallet; // Возвращаем обратно для дальнейших экспериментов...
		Money dobavka(5, 5, 5.0); // Для проверок операторов += и -=
		cout << "Your wallet with more 5pd.5sh.5p.:" << endl;
		wallet += dobavka; // Проверка на +=
		cout << wallet << endl;
		wallet -= dobavka; // И соответственно проверка на -=
		cout << "After moving those 5pd.5sh.5. back from the wallet: " << endl;
		cout << wallet << endl;
		if (price_of_product - dobavka == dobavka) // Проверка на равенство
		{
			cout << "The compare operation works correctly" << endl;
		}
		else
		{
			cout << "The compare operation does not work correctly!!!" << endl;
		}
		Money empty_wallet; // Проверка конструктора по умолчанию
		cout << "Just some empty wallet: " << endl;
		cout << empty_wallet;
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}