#include <windows.h>
#include <iostream>
using namespace std;

struct employee
{
	char full_name[50];
	int depart_number;
	char job_post[30];
	int job_start_date;
};

void PrintFileInfo()
{
	printf_s("All information from file \"File_New.dat\" :\n");					// Начало вывода всей информации из файла

	LPCWSTR fn = L"File_New.dat";												// Строка с именем файла, что нам необходимо открыть

	// Запоминает дескриптор файла
	HANDLE File = CreateFile(
		fn,																		// Имя файла
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	employee object;															// Переменная, в которой будет хранится структура с одним сотрудником
	DWORD n;																	// Счётчик, с помощью которого мы узнаем, что дошли до конца файла

	// Чтение данных из файла и вывод их на консоль
	while (ReadFile(File, &object, sizeof(object), &n, NULL) && n != 0)
	{
		printf_s("%s\n%d\n%s\n%d\n\n", object.full_name, object.depart_number, object.job_post, object.job_start_date);
	}

	CloseHandle(File);															// Закрываем дескриптор файла
}

int main()
{
	PrintFileInfo();															// Печатаем всю имеющуюся информацию из файла

	printf_s("Now, enter the number of structure to be changed: ");				// Начало вывода всей информации из файла

	int structure_num = 0;														// Номер структуры, которую необходимо изменить
	scanf_s("%d", &structure_num);												// Ввод пользователем имени структуры для изменения

	char buffer[1000];															// Строка, в которой мы будем собирать аргументы командной строки для второго процесса

	sprintf_s(buffer, "%s %d", "Daughter.exe", structure_num);					// Аргументы командной строки: exe-шка второго процесса, номер структуры

	STARTUPINFOA Daughter;
	ZeroMemory(&Daughter, sizeof(Daughter));									// Зануление памяти (чтобы не было мусора)
	Daughter.cb = sizeof(Daughter);												// Запоминаем размер структуры
	PROCESS_INFORMATION Daughter_Info;
	ZeroMemory(&Daughter_Info, sizeof(Daughter_Info));							// Зануление памяти (чтобы не было мусора)

	CreateProcessA(NULL,
		buffer,																	// Аргументы командной строки для этого процесса
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&Daughter,
		&Daughter_Info
	);

	printf_s("\nWaiting until process Daughter finishes his work...\n");		// Осведомляем пользователя о том, что мы ждём завершения работы процесса Daugther

	WaitForSingleObject(Daughter_Info.hProcess, INFINITE);						// Ждем, пока Daughter закончит свою работу

	printf_s("\nProcess Dauther finished his work! File information has been changed.\n\n");// Осведомляем пользователя о том, что процесс Daughter завершил свою работу

	PrintFileInfo();															// Снова печатаем содержимое файла

	CloseHandle(Daughter_Info.hProcess);										// Закрываем дескриптор процесса Daughter
	CloseHandle(Daughter_Info.hThread);											// Закрывает дескриптор треда Daughter

	return 0;
}