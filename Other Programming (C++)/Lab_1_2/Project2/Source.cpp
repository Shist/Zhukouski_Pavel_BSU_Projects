#include <iostream> 
using namespace std;

int main()
{
	cout << "Please, enter any THREE-DIGIT number\n";
	int num, hund, dec, ones;
	cin >> num;
	if (100 <= num & num <= 999) // Защита от дурака 
	{
		hund = num / 100;
		num %= 100;
		dec = num / 10;
		num %= 10;
		ones = num;
		cout << "The sum of digits is\n";
		cout << hund + dec + ones << endl;
	}
	else
	{
		cout << "Impossible to calculate! The number you entered is not three-digit or it is not a number in general!\n";
	}
	return 0;
}