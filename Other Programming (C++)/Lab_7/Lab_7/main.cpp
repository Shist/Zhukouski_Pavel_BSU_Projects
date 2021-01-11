#include <iostream>
#include <fstream>
#include <cstring> // Подключаем cstring для функций strlen и strcpy
#pragma warning (disable: 4996) // Отключаем ругательства компилятора
using namespace std;

bool check = false;
fstream open_file(const char *prompt, char *file_name, ios_base::openmode mode)
{ // Вводим функцию, с помощью которой будем строить диалоговое окно и открывать файлы
	cout << prompt << '\n'; // В параметре prompt будем хранить (а потом выводить) сообщение пользователю
	char *new_name = new char[256]; // Выделяем память под массив символов для имени файлов
	new_name[0] = '\0'; // Зануляем строку
	cin.getline(new_name, 256);
	if (strlen(new_name) != 0) // Если длина имени файла не равна нулю, то...
	{
		strcpy(file_name + '.' + 't' + 'x' + 't', new_name); // Присваиваем значению строки это имя файла + добавляем расширение .txt
	}
	delete[] new_name; // Очищаем память от массива
	return fstream(file_name, mode);
}

int main()
{
	char* file_name = new char[256]; // Выделяем память под массив символов для имени файлов
	strcpy(file_name, "IN.TXT"); // С помощью функции strcpy заносим в file_name значение IN.TXT
	fstream fin = open_file("Enter file name in which you store input data...\n"
		"If you enter nothing then file named IN.txt will be opened", 
		file_name, ios_base::in); // Создаем диалоговое окно для файла, который будем читать...
	if (fin.is_open()) // Если файл открывается, выполняем программу...
	{
		if (fin.peek() == EOF) // Проверяем файл на пустоту
		{
			cerr << "File IN.TXT is empty!";
			return 2;
		}
		strcpy(file_name, "OUT.TXT"); // С помощью функции strcpy заносим в file_name значение OUT.TXT
		fstream fout = open_file("Enter file name in which you want to store the result of calculations...\n"
			"If you enter nothing then file name will be OUT.txt",
			file_name, ios_base::out); // Создаем диалоговое окно для файла, в который будем выводить вычисления...
		int str_num = 1; // В этой переменной будем хранить номер строчки в файле
		int kol_vo = 0; // В этой переменной будем хранить количество повторений пустых строчек
		int group_num = 0; // В этой переменной будем хранить номер группы
		bool str_empty = true; // Вводим флажок, в котором будем хранить информацию о том, является ли строка пустой
		char symbol; // Вводим эту переменную, чтобы читать символы
		while ((symbol = fin.get()) != EOF) // Пока содержимое файла не закончилось, делаем следующее...
		{
			if (symbol != '\n') // Если символ не является отступлением на новую строчку, то делаем следующее...
			{
				if (symbol != ' ') // Если символ не является пробелом, то делаем следующее...
				{
					str_empty = false; // Говорим, что эта строка не пустая
					if (kol_vo != 0) // Если до этой строчки были пустые строчки, то делаем следующее...
					{
						group_num++; // Делаем инкремент номера группы, т.к. мы создаем новую группу
						fout << "The " << group_num << " group: " <<
							kol_vo << " repetitions, the line number of the beginning of the group is " << str_num - kol_vo<< endl;
					}
					kol_vo = 0; // Зануляем количество пустых строк до новой группы
				}
			}
			else // Если же символ является отступлением на новую строчку, то делаем вот, что...
			{
				if (str_empty) // Если эта строчка была пустой, то...
				{
					kol_vo++; // Повышаем количество пустых строчек на единицу
				}
				str_num++; // Т.к. мы перешли на новую строку, то делаем инкремент номера строки
				str_empty = true; // Для новой строчки ставим флажок пустоты на true
			}
		}
		if (str_empty) kol_vo++; // Если последняя строчка была пустаая, то делаем инкремент переменной kol_vo
		if (kol_vo != 0) // Если так вышло, что последняя строчка (строчки) в файле оказалась (оказались) пустой (пустыми), то
		{
			group_num++; // Делаем инкремент номера группы, т.к. мы создаем новую группу
			fout << "The " << group_num << " group: " <<
				kol_vo << " repetitions, the line number of the beginning of the group is " << str_num - kol_vo + 1 << endl;
		}
		if (group_num == 0) // Проверяем, были ли пустые строки в нашем файле вообще
		{
			fout << "There are no any empty lines in file!" << endl;
		}
		fin.close(); // Закрываем входящий файл 
		fout.close(); // Закрывай выходящий файл
	}
	else
	{
		cerr << "Input file did not open!";
		return 1;
	}
	delete[] file_name; // Очищаем память от массива
	return 0;
}