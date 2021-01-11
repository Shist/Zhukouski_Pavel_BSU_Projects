#include <iostream>
#include <ctime>
using namespace std;

long long Euler_function(long long n)
{
	long long result = n;
	for (long long i = 2; i*i <= n; ++i)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	if (n > 1)
		result -= result / n;
	return result;
}

const double Pi = 3.141592653589793238463;

int main()
{
	system("color 2");
	long long N;
	double sum = 0.0;
	cout << "Enter the number to which the calculation will be: ";
	cin >> N;
	cout << "The calculation will be at [1; " << N << "]\n";
	double formula_result = 6.0 / (Pi*Pi);
	cout << "The value of formula: " << formula_result << "\n";
	double our_result = 0.0;
	for (long long k = 1; k < N; k++)
	{
		sum += Euler_function(k);
		if (k % 100000 == 0)
		{
			cout << "The current value of calculations: " << our_result << "\n";
			our_result = 2 * sum / (N*N);
			cout << "The difference: " << abs(formula_result - our_result) << "\n";
			cout << "Current time of work: " << clock() / 1000.0 << " seconds" << endl << endl;
		}
	}
	cout << "The time of work of the current algorithm: " << clock() / 1000.0 << " seconds" << endl;
	return 0;
}
