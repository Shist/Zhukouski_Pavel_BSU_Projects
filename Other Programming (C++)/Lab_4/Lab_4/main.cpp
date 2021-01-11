#include <iostream>
#pragma warning(disable: 4996) // Отключает ругательства компилятора
using namespace std;

char *strcat(char *strDestination, const char *strSource) // Собственная реализация стандартной функции strcat
{
	int endPos = 0, i = 0;
	while (strDestination[endPos] != '\0') // Ищем индекс, при котором наблюдается конец первой строки
	{
		endPos++;
	}
	while (strSource[i] != '\0') // Пока индекс, при котором наблюдается конец второй строки, не обнаружен, делаем следующее:
	{
		strDestination[endPos+i] = strSource[i]; // Добавляем символы из второй строки к концу первой строки
		i++;
	}
	strDestination[endPos + i] = '\0';
	return strDestination; // Возвращаем значение первой строки
}
int main() // Основная часть программы
{
	char *arr1 = new char[301]; // Выделяем память под первую строку, которую введем в консоли
	char *arr2 = new char[301]; // Выделяем память под вторую строку, которую введем в консоли
	cout << "Enter the first line:\n";
	cin.getline(arr1, 301); // Вводим значение 1-ой строки с консоли
	cout << "Enter the second line you want to connect with the first:\n";
	cin.getline(arr2, 301); // Вводим значение 2-ой строки с консоли
	strcat(arr1, arr2); // Вызов функции
	cout << "The resulting line is the next:\n";
	cout << arr1 << endl; // Вывод получившейся строки
	delete []arr1; // Освобождаем память
	delete []arr2; // Освобождаем память
	return 0;
}