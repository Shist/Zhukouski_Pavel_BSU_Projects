#include <iostream>
#include <cmath> // Подключаем библиотеку cmath, чтобы с помощью простейших математических функций описать наши три функции
// Вариант 4
using namespace std;

double function1(double x)
{ // Код первой функции
	double result = 1.0;
	result = x * atan(x);
	return result;
}

double function2(double x)
{ // Код второй функции
	double result = 1.0;
	result = (1.0 / (1.0 + sqrt(x)));
	return result;
}

double function3(double x)
{ // Код третьей функции
	double result = 1.0;
	result = (2.0 / (1.0 - 4.0 * x));
	return result;
}

double integral(double (*function)(double), double t, double g, double epsilon, int& razb)
{ // Функция вычисления интеграла с заданной точностью методом трапеции
	razb = 2; // Эта переменная будет показывать нам количество разбиений, которое потребовалось 
	double result1 = 10.0, result2 = 0, step;
	while (abs(result2 - result1) >= epsilon) // Пока не выполняется точность, производим итерации...
	{
		result1 = result2; // В переменной result1 храним данные о прошлых (менее точных) измерениях
		result2 = 0; // Присваиваем result2 значение нуля, чтобы произвести новые (более точные) вычисления
		razb *= 2; // С каждой итерацией умножаем количество разбиений вдвое
		step = (g - t) / razb; // В переменной step (шаг) храним значение разности границ интервала, деленной на количество разбиений
		for (int i = 0; i < razb; i++)
		{ // Складываем площади всех получившихся после разбиений трапеций в одну площадь
			result2 += (function(t + i * step) + function(t + (i + 1) * step)) / 2 * step;
		} // Как правило, с каждой итерацией площадь result2 становится все ближе к реальному значению площади интеграла
	}
	return result2; // Возвращаем значение функции
}

int main()
{
	int razb1, razb2, razb3; // Переменные, хранящие данные о том, сколько разбиений потребовалось для каждой из трех функций
	double epsilon, int_1, int_2, int_3; // Переменные, соответственно хранящие данные о точности, первом интеграле, втором интеграле, третьем интеграле
	const double a1 = 0.0, b1 = 1.7, a2 = 0.0, b2 = 2.0, a3 = -2.0, b3 = -1.2; // Переменные, задающие интервалы для интегралов
	cout << "Enter the desired accuracy of calculations:\n"; // Вывод сообщения "Введите желаемую точность:"
	cin >> epsilon; // Ввод желаемой точности
	if (epsilon < 0.0000001 || epsilon > 0.1)
	{ // Защита от дурака
		cout << "Error. The entered value of epsillon is incorrect or too small.";
		return 1;
	}
	int_1 = integral(function1, a1, b1, epsilon, razb1); // Вычисляем интеграл первой функции
	int_2 = integral(function2, a2, b2, epsilon, razb2); // Вычисляем интеграл второй функции
	int_3 = integral(function3, a3, b3, epsilon, razb3); // Вычисляем интеграл третьей функции
	cout.precision(ceil(log10(1/epsilon))); // Задаем точность для вывода
	cout << "The value of the first calculated integral is:\n" << int_1 << endl; // Вывод первого интеграла
	cout << "The number of splits on which the specified accuracy is achieved in the first integral:\n" << razb1 << endl; // Вывод количества разбиений, потребовавшихя для вычисления с заданной точностью первого интеграла
	cout << "The value of the second calculated integral is:\n" << int_2 << endl; // Вывод второго интеграла
	cout << "The number of splits on which the specified accuracy is achieved in the second integral:\n" << razb2 << endl; // Вывод количества разбиений, потребовавшихя для вычисления с заданной точностью второго интеграла
	cout << "The value of the third calculated integral is:\n" << int_3 << endl; // Вывод третьего интеграла
	cout << "The number of splits on which the specified accuracy is achieved in the third integral:\n" << razb3 << endl; // Вывод количества разбиений, потребовавшихя для вычисления с заданной точностью третьего интеграла
	return 0;
}