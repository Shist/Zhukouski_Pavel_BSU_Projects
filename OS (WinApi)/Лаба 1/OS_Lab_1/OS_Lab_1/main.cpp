#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

// Структура записей файла, которые вводятся с консоли
struct employee
{
	int num;			// Идентификационный номер сотрудника
	char name[10];		// Имя сотрудника
	double hours;		// Количество отработанных часов
};

int main()
{
	char binary_file_name[256];

	// Ввод данных
	cout << "Enter binary file name: ";
	cin.getline(binary_file_name, 256);						// Ввод имени бинарного файла
	int records_num = 0;									// Количество записей
	cout << "Enter the number of records in that file: ";
	cin >> records_num;										// Ввод количества записей
	cin.ignore();											// Отбрасывает один символ

	STARTUPINFO Creator;
	ZeroMemory(&Creator, sizeof(Creator));					// Зануление памяти (чтобы не было мусора)
	Creator.cb = sizeof(Creator);							// Запоминаем размер структуры
	PROCESS_INFORMATION Creator_Info;
	ZeroMemory(&Creator_Info, sizeof(Creator_Info));		// Зануление памяти (чтобы не было мусора)
	char buffer[1000];
	sprintf_s(buffer, "%s %s %d", "OS_Lab_1_Creator.exe", binary_file_name, records_num);

	CreateProcess(NULL,
		buffer,				// Аргументы командной строки для этого процесса
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&Creator,
		&Creator_Info
	);

	WaitForSingleObject(Creator_Info.hProcess, INFINITE);			// Ждем, пока Creator закончит свою работу

	CloseHandle(Creator_Info.hProcess);								// Закрываем дескриптор процесса Creator
	CloseHandle(Creator_Info.hThread);								// Закрывает дескриптор треда Creator

	cout << "Information, written to binary file:" << endl;
	buffer[0] = '\0';
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", binary_file_name);
	ifstream fin(buffer, ios::binary);
	fin.read((char*)&records_num, sizeof(int));						// Считываем информацию о количестве сотрудников из бинарного файла
	employee* records = new employee[records_num];

	// Пока содержимое входного файла не закончилось, делаем считывание и обработку данных...
	for (int i = 0; i < records_num; i++)
	{
		fin.read((char*)&records[i], sizeof(employee));
	}

	cout << records[0].num << " " << records[0].name << " " << records[0].hours;			// Номер Имя Кол-во часов
	for (int i = 1; i < records_num; i++)													// Выводим сначала первый, потом endl вставляем в цикл, чтобы в файле не было лишней пустой строки
		cout << endl << records[i].num << " " << records[i].name << " " << records[i].hours;

	delete[] records;

	fin.close();

	char output_file_name[256];
	cout << "\n\nEnter output file name: ";
	cin.getline(output_file_name, 256);									// Ввод имени выходного файла
	double salary_per_hour = 0.0;										// Зарплата за час работы
	cout << "Enter salary value per one hour: ";
	cin >> salary_per_hour;												// Считываем зарплату за час работы
	buffer[0] = '\0';
	sprintf_s(buffer, "%s %s %s %lf", "OS_Lab_1_Reporter.exe", binary_file_name, output_file_name, salary_per_hour);

	STARTUPINFO Reporter;
	ZeroMemory(&Reporter, sizeof(Reporter));							// Зануление памяти (чтобы не было мусора)
	Reporter.cb = sizeof(Reporter);										// Запоминаем размер структуры
	PROCESS_INFORMATION Reporter_Info;
	ZeroMemory(&Reporter_Info, sizeof(Reporter_Info));					// Зануление памяти (чтобы не было мусора)
	CreateProcess(NULL,
		buffer,															// Аргументы командной строки для этого процесса
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&Reporter,
		&Reporter_Info
	);
	WaitForSingleObject(Reporter_Info.hProcess, INFINITE);				// Ждем, пока Creator закончит свою работу
	CloseHandle(Reporter_Info.hProcess);								// Закрываем дескриптор процесса Reporter
	CloseHandle(Reporter_Info.hThread);									// Закрывает дескриптор треда Reporter
	buffer[0] = '\0';
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", output_file_name);
	ifstream fin_ReportInfo(buffer);
	cout << endl << "Information, read from output file:" << endl;

	// Пока содержимое входного файла не закончилось, делаем считывание и обработку данных...
	for (int i = 0; i < records_num; i++)
	{
		buffer[0] = '\0';
		fin_ReportInfo.getline(buffer, 1000);
		for (int i = 0; buffer[i] != '\0'; i++)
			printf("%c", buffer[i]);
		cout << endl;
	}
	fin_ReportInfo.close();
	return 0;
}