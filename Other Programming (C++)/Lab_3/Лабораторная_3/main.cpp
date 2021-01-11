#include <iostream>
#include <random> 
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	double epsillon, sum = 1, y;
	cout << "Введите точность вычислений:\n";
	cin >> epsillon;
	if (epsillon < 0.000001 || epsillon > 1) // Защита от дурака
	{
		cout << "Введено некорректное или слишком маленькое значение epsillon" << endl;
		return 0;
	}
	random_device generator;
	uniform_real_distribution<double> distribution(-1, 1);
	double x = distribution(generator), a = x; // Программа выбирает случайное число x из диапазона
	cout << "На интервале вещественных чисел R выбран x, равный: " << x << "\n";
	int i = 1;
	while (abs(a) >= epsillon/2) // abs(x) - модуль числа x
	{
		sum += a;
		a *= x / (i + 1); // Алгоритм вычисления суммы элементов в правой части равенства
		i++;
	}
	y = abs(sum-exp(x)); // Вычисляем разность получившихся значений
	cout << setprecision(ceil(log10(1 / epsillon))) << "Значение левой части равно: " << exp(x) << endl << // setpresition(...) - задает точность, зависящую от epsillon
	 "Значение правой части равно: " << sum << endl << "Погрешность составляет: " << y << endl; // exp(x) = e^x
	if (y < epsillon)
	{
		cout << "Заданная точность выполняется" << endl;
	}
	else
	{
		cout << "Заданная точность не выполняется" << endl;
	}
	return 0;
}

/* На случай, если понадобится ввести начало и конец диапазона с консоли:
double k, p;
cout << "Введите число, соответствующее началу диапазона: ";
cin >> k;
cout << "Введите число, соответствующее концу диапазона: ";
cin >> p;
uniform_real_distribution<double> distribution(k, p);
*/