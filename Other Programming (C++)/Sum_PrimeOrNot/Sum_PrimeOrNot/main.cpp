#include <iostream>
using namespace std;

// ‘ункци€, определ€юща€, €вл€етс€ ли данное число простым
bool IsPrime(int num)
{
	if (num == 1 || num == 0)
		return false; // 0 - вообще не натуральное число, 1 - ни простое, ни составное
	for (int i = 2; i * i < num; i++) // ѕровер€ем все делители до корн€ текущего числа
		if (num % i == 0) // ≈сли хот€ бы на один делитс€, то число составное
			return false;
	return true; // ≈сли дошли сюда, значит число простое
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