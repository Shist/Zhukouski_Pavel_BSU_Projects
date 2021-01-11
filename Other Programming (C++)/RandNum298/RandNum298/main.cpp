#include <iostream>
#include <string>
#include <random>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	random_device generator;
	uniform_int_distribution<int> distribution(1, 298);
	cout << "Привет, Илья. Эта программа поможет тебе выбрать число от 1 до 298." << endl;
	while (true)
	{
		cout << "Введи \"exit\" для выхода или прожми Enter, чтобы подобрать новое число.\n";
		string temp;
		getline(cin, temp);
		if (temp == "exit")
			break;
		else
			cout << "Выбранное число - " << distribution(generator) << endl;
	}
	return 0;
}