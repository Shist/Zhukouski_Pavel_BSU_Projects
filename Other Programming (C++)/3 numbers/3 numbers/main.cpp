#include <iostream>
#include <random>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	random_device generator;
	uniform_int_distribution<int> distribution(1, 99);
	int a = distribution(generator);
	int b = distribution(generator);
	int c = distribution(generator);
	cout << "Сумма первого и второго чисел равна: " << a + b << endl;
	cout << "Сумма второго и третьего чисел равна: " << b + c << endl;
	cout << "А сумма первого и третьего чисел равна: " << a + c << endl;
	cout << "Найдите все эти числа по отдельности, а в ответ запишите СУММУ ИХ ЦИФР" << endl;
	cout << "Ваш ответ: ";
	int sum = ((a % 10) + (a / 10) + (b % 10) + (b / 10) + (c % 10) + (c / 10));
	int num = 0;
	while (num != sum)
	{
		cin >> num;
		if (num == sum)
		{
			cout << "Совершенно верно! Поздравляю, вы победили в этой игре!" << endl;
		}
		else
		{
			cout << "Неверно, попробуйте еще раз: ";
		}
	}
	system("pause");
	return 0;
}