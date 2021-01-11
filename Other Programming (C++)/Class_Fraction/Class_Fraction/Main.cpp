#include "Fraction.h"
using namespace std;

int main()
{
	try
	{
		long long a, b;
		cout << "Enter numerator for your 1st fraction: " << endl;
		cin >> a;
		cout << "Enter denominator for your 1st fraction: " << endl;
		cin >> b;
		Fraction example_1(a, b);
		cout << "Enter numerator for your 2st fraction: " << endl;
		cin >> a;
		cout << "Enter denominator for your 2st fraction: " << endl;
		cin >> b;
		Fraction example_2(a, b);
		cout << example_1.SeeDouble() << endl;
		cout << example_2.SeeDouble() << endl;
		Fraction example_3 = example_1 * example_2;
		cout << example_3.SeeDouble() << endl;
	}
	catch(exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}