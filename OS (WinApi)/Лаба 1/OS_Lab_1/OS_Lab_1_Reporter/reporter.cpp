#include <fstream>
using namespace std;

struct employee
{					// Структура записей файла, которые вводятся с консоли
	int num;		// Идентификационный номер сотрудника
	char name[10];	// Имя сотрудника
	double hours;	// Количество отработанных часов
};

// Структура сотрудника
struct employee_sal
{
	int num;		// Идентификационный номер сотрудника
	char name[10];	// Имя сотрудника
	double hours;	// Количество отработанных часов
	double salary;	// Зарплата
};

// На вводе ожидается (имя исходного бинарного файла) (имя файла отчёта) (оплата за час работы)
int main(int argc, char* argv[])
{
	char buffer[1000];
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", argv[1]);
	ifstream fin(buffer, ios::binary);					// Открывает бинарный файл (1 аргумент в консоли - имя исходного бинарного файла)

	buffer[0] = '\0';
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", argv[2]);
	ofstream fout(buffer);								// Создает текстовый файл (2 аргумент в консоли - имя файла)

	double salary_per_hour = atof(argv[3]);				// Оплата за час работы (atoi(str) - преобразут строку str в дробное число)
	int records_num = 0;
	fin.read((char*)&records_num, sizeof(int));			// Считываем информацию о количестве сотрудников
	employee_sal* records = new employee_sal[records_num];

	// Пока содержимое входного файла не закончилось, делаем считывание и обработку данных...
	for (int i = 0; i < records_num; i++)
	{
		employee temp;
		fin.read((char*)&temp, sizeof(employee));
		records[i].num = temp.num;
		strcpy_s(records[i].name, temp.name);
		records[i].hours = temp.hours;
		records[i].salary = salary_per_hour * records[i].hours;
	}

	fout << records[0].num << " " << records[0].name << " " << records[0].hours << " " << records[0].salary;				// Номер Имя Кол-во часов Зарплата
	for (int i = 1; i < records_num; i++)																					// Выводим сначала первый, потом endl вставляем в цикл, чтобы в файле не было лишней пустой строки
		fout << endl << records[i].num << " " << records[i].name << " " << records[i].hours << " " << records[i].salary;

	fin.close();
	fout.close();

	delete[] records;

	return 0;
}