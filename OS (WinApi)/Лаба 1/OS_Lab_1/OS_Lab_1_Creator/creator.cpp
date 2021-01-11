#include <iostream>
#include <fstream>
using namespace std;

struct employee
{					// Структура записей файла, которые вводятся с консоли
	int num;		// Идентификационный номер сотрудника
	char name[10];	// Имя сотрудника
	double hours;	// Количество отработанных часов
};

// На вводе ожидается (имя файла) (кол-во записей)
int main(int argc, char* argv[])
{
	char buffer[1000];
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", argv[1]);
	ofstream fout(buffer, ios::binary);		// Создает бинарный файл (1 аргумент в консоли - имя файла)

	int records_num = atoi(argv[2]);		// 2-ой аргумент в консоли - количество записей (atoi(str) - преобразут строку str в целое число) 
	employee* records = new employee[records_num];

	cout << endl << "So, now enter information about all the " << records_num << " employees:" << endl << endl;
	for (int i = 0; i < records_num; i++)
	{
		cout << "Employee number " << (i + 1) << ": ";
		cin >> records[i].num;
		cin >> records[i].name;
		cin >> records[i].hours;
		cout << endl;
	}

	// Вывод информации о каждом сотруднике в выходной файл:
	fout.write((char*)&records_num, sizeof(int));	// Выводим количество сотрудников
	for (int i = 0; i < records_num; i++)			// Выводим сначала первый, потом endl вставляем в цикл, чтобы в файле не было лишней пустой строки
		fout.write((char*)&records[i], sizeof(employee));

	fout.close();

	delete[] records;

	return 0;
}