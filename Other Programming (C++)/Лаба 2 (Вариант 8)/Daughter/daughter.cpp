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

int main(int argc, char* argv[])
{
	printf_s("Process Daughter started his work...\n\n");	// Уведомляем пользователя, что второй процесс начал свою работу

	printf_s("Process Daughter got the next command line: \"%s %s\"\n\n", argv[0], argv[1]);	// Выводим всё то, что было получено через командную строку

	int struct_to_change = atoi(argv[1]);					// Считываем из командной строки 1-ый аргумент и превращаем его из строки в целое число

	printf_s("So, you're going to change information about structure number \"%d\".\n\n", struct_to_change);	// Вывод для пользователя

	employee new_object;									// Структура с новым объектом, который мы изменим в этом процесса

	printf_s("Enter new full name for structure number \"%d\": ", struct_to_change);
	scanf_s("%s", &(new_object.full_name), (unsigned)_countof(new_object.full_name));

	printf_s("Enter new department number for structure number \"%d\": ", struct_to_change);
	scanf_s("%d", &(new_object.depart_number));

	printf_s("Enter new job post for structure number \"%d\": ", struct_to_change);
	scanf_s("%s", &(new_object.job_post), (unsigned)_countof(new_object.job_post));

	printf_s("Enter new job start date for structure number \"%d\": ", struct_to_change);
	scanf_s("%d", &(new_object.job_start_date));

	LPCWSTR fn = L"File_New.dat";							// Строка с именем файла, что нам необходимо открыть

	// Запоминает дескриптор файла
	HANDLE File = CreateFile(
		fn,													// Имя файла
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	employee object;										// Переменная, в которой будет хранится структура с одним сотрудником
	DWORD n;												// Счётчик, с помощью которого мы узнаем, что дошли до конца файла
	int curr_struct_num = 0;								// Чтобы подсчитать, сколько у нас стурктур

	// Чтение данных из файла для подсчёта их количества
	while (ReadFile(File, &object, sizeof(object), &n, NULL) && n != 0)
		curr_struct_num++;									// Подсчитываем количество структур

	employee* objects = new employee[curr_struct_num];		// Создаем массив из curr_struct_num структур

	SetFilePointer(File, 0, 0, FILE_BEGIN);					// Становимся снова на начало файла

	int i = 0;												// Счётчик

	while (ReadFile(File, &objects[i], sizeof(object), &n, NULL) && n != 0)
	{
		if (struct_to_change == (i + 1))
		{ // Если номер структуры соответствуют тому номеру, что мы изменяли, то вносим новую информацию в нужную нам структуру
			strcpy_s(objects[i].full_name, new_object.full_name);	// Копируем новое значение имени в старое
			objects[i].depart_number = new_object.depart_number;	// Копируем новое значение номера департамента в старое
			strcpy_s(objects[i].job_post, new_object.job_post);		// Копируем новое значений рабочей должности в старое
			objects[i].job_start_date = new_object.job_start_date;	// Копируем новое значение года начала работы в старое
		}
		i++;												// Записываем все данные из старого файла в массив
	}

	CloseHandle(File);										// Закрываем дескриптор файла

	// Создаём дескриптор файла для ПЕРЕЗАПИСИ (чит. CREATE_ALWAYS)
	File = CreateFile(
		fn,													// Имя файла
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS, // ПЕРЕЗАПИСЬ ФАЙЛА
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	for (int i = 0; i < curr_struct_num; i++) // Запись новых данных в файл
		WriteFile(File, &objects[i], sizeof(employee), &n, NULL);

	CloseHandle(File);										// Закрываем дескриптор файла

	delete[] objects;										// Очищаем память от массива структур

	return 0;
}