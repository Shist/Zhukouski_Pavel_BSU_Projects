#include <iostream>
#pragma warning(disable: 4996) // Отключает ругательства компилятора

using namespace std;

const int MAXLENGTH = 300; // Вводим константу для того, чтобы задать размерность строки

bool isInStr(const char *str, int c) // Вводим функцию isInStr, чтобы с ее помощью сделать функцию strtok
{
	int i = 0;
	do
	{
		if (str[i] == c) return true;
		i++;
	} while (str[i - 1] != '\0');
	return false;
}

char *strtok(char *str, const char *delim) // Вводим функцию strtok, которая пригодится нам в основной части программы 
{
	static char *curr_pos, preview;
	if (str != NULL)
	{
		curr_pos = str;
		preview = '\0';
	}
	char *startToken;
	int i = 0;
	if (*curr_pos == '\0' && preview == '\0') return NULL;
	else if (*curr_pos == '\0') curr_pos++;
	while ((curr_pos[i] != '\0') && (isInStr(delim, curr_pos[i]))) i++;
	if (curr_pos == '\0')
	{
		curr_pos = NULL;
		return NULL;
	}
	startToken = curr_pos + i;
	while (!isInStr(delim, curr_pos[i])) i++;
	curr_pos += i;
	preview = *curr_pos;
	*curr_pos = '\0';
	return startToken;
}

char *strcpy(char *p, const char *v) // Вводим также функцию strcpy, чтобы присвоить строчке значение в основной программе
{
	char *st = p;
	while (*v)
		*(p++) = *(v++);
	++(*p) = '\0';
	return st;
}

int main()
{
	char *str = new char[MAXLENGTH + 1]; // Выделяем память под нашу строку
	cout << "Enter string:\n"; // Ввод строки
	cin.getline(str, MAXLENGTH + 1); // Вводим в консоль нашу строку (не более 300 символов)
	char *pos = strtok(str, " "); // Вводим функцию, которая ищет пробелы в нашей строке
	char *word = new char[MAXLENGTH + 1]; // Выделяем память под вспомогательную строку word, в которой мы будем хранить результат
	int distinct, minDistinct = MAXLENGTH + 1; // Вводим несколько переменных, которые понадобятся в создании алгоритма
	bool have[256]; // Вводим bool-массив под 256 элементов, который будет хранить информацию о том, встретился ли нам какой-то символ в строке
	while (pos != NULL)
	{ // Здесь начинается алгоритм, который подсчитывает количество различных символов для каждого слова в строке
		distinct = 0; 
		for (int i = 0; i < 256; i++)
			have[i] = false; // Инициализируем каждый элемент массива bool под false
		for (int i = 0; pos[i] != '\0'; i++) // Перебираем все символы в слове
			if (!have[pos[i] - '\0']) // Проверка на то, встречался ли нам этот символ раньше
			{
				have[pos[i] - '\0'] = true; // Говорим, что символ pos[i] нам встретился
				distinct++;
			}
		if (distinct < minDistinct)
		{
			minDistinct = distinct;
			strcpy(word, pos); // При выполненных условиях присваиваем строчке word значение строчки pos, являющейся словом с минимальным количеством символов
		}
		pos = strtok(NULL, " ");
	}
	cout << "Your required word is:\n";
	cout << word << endl;
	delete []str; // Освобождаем память
	delete []word; // Освбождаем память
	return 0;
}