#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>

#define MAXLENGTH 101 // Здесь задаем размер строки (101 = 100 символов + '\0')
DWORD GetProcessID(char*);// функция получения ID процесса
// DWORD - 32-битное беззнаковое целое. Аналоги: unsigned long int, UINT.

int main(void)
{
	//-----------------------------ОБЪЯВЛЕНИЕ ВСЕХ ПЕРЕМЕННЫХ-----------------------------

	LPCTSTR pipename = "\\\\.\\pipe\\MyPipe"; // Имя канала
	// LPCTSTR – Указатель на константную строку, без UNICODE.  От фразы long pointer constant TCHAR string. Это надстройка функции LPCSTR.
	HANDLE hProcessB; // Дескриптор процесса B
	LPVOID szAddress; // Адрес в памяти процесса B (LPVOID - указатель на любой тип)
	DWORD dBuf;	// Буффер (имеет промежуточное значение, DWORD - аналог Unsigned INT32)
	BOOL Success; // Флаг успешного открытия/считывания/записи
	DWORD szSize = sizeof(char) * MAXLENGTH; // Размер вводимой строки
	char* str = (char*)malloc(szSize); // Сама строка
	HANDLE hPipe = INVALID_HANDLE_VALUE; // Дескриптор канала

	//------------------------------------------------------------------------------------

	printf("Enter your string: ");
	gets_s(str, MAXLENGTH - 1); // Ввод строки (get_s - получает строку str из потока stdin, размер буфера MAXLENGTH - 1)

	printf("Opening ProcessB...");
	hProcessB = OpenProcess(
		PROCESS_ALL_ACCESS, // Устанавливает уровень доступа к объекту процесса
		FALSE, // Параметр дескриптора наследования (false - наследники не будут наследовать дескриптор)
		GetProcessID("SP_Lab_3_Process_B.exe")); // ID процесса (в данном случае - процесса B)
	if (hProcessB == INVALID_HANDLE_VALUE)
	{
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	printf("Success!!!\nAllocating memory for ProcessB...");
	// VirtualAllocEx - Резервирует, фиксирует или изменяет состояние области памяти в виртуальном адресном пространстве
	// указанного процесса. Функция инициализирует память, выделенную нулю.
	/*Если функция завершается успешно, возвращаемое значение является базовым адресом выделенной области страниц.
	Если функция не работает, возвращаемое значение равно NULL.*/
	szAddress = VirtualAllocEx( // В адресном пространстве процесса B выделяем память
		hProcessB, // Дескриптор процесса (в данном случае - процесса B)
		0, // Куда выделить память? Так как мы ввели 0, система сама решает, где выделять
		szSize, // Объём резервируемой памяти
		MEM_RESERVE | // Зарезервировать страницы
		MEM_COMMIT, // Выделяем физическую память
		PAGE_EXECUTE_READWRITE); // Атрибут защиты
	/*Попытка зафиксировать определенный диапазон адресов путем указания MEM_COMMIT без MEM_RESERVE и ненулевого lpAddress завершается неудачей, 
	если весь диапазон уже не зарезервирован. Полученный код ошибки - ERROR_INVALID_ADDRESS.*/

	printf("Success!!!\nWriting your string in ProcessB memory...");
	Success = WriteProcessMemory( // Записывает данные в область памяти в указанном процессе. Вся область для записи должна быть доступна, иначе операция завершится неудачно.
		hProcessB, // Дескриптор процесса (в данном случае - процесса B)
		szAddress, // Куда записывать
		str, // Что записывать
		szSize, // Объём записываемых данных
		0); // Указатель на переменную, которая получает число байтов, переданное в указанный процесс (игнорируется, если 0)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	printf("Success!!!\nConnecting to named pipe...");
	while (hPipe == INVALID_HANDLE_VALUE) {
		hPipe = CreateFile( // Подключаемся к тому именованному каналу, что создали в процессе B
			pipename, // Имя именованного канала (файла)
			GENERIC_READ | // Требуем доступ к чтению и записи
			GENERIC_WRITE,
			0, // Без совместного доступа (объект не может совместно использоваться, и не может быть открыт снова до тех пор, пока дескриптор не закроется)
			NULL, // Без дескрипторов защиты
			OPEN_EXISTING, // Открываем существующий канал
			0, // Атрибуты файла по умолчанию
			NULL); // Без дескриптора файла шаблона
	}

	printf("Success!!!\nWriting memory address...");
	dBuf = (DWORD)szAddress; // Сохраняем данные адреса в буфер
	Success = WriteFile( // Записываем в именнованый канал адрес, в котором хранится строка
		hPipe, // Дескриптор канала (файла)
		&dBuf, // Данные для записи (в данном случае - адрес памяти в процессе B) 
		sizeof(dBuf), // Объём записываемых данных (в байтах)
		NULL, // Количество записанных данных (не используем)
		NULL); // Асинхронный буфер (не используем)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	printf("Success!!!\nWaiting answer from ProcessB...");
	Success = ReadFile( // Получаем ответ от процесса B, что он получил адрес строки
		hPipe, // Имя именованного канала (дескриптор файла)
		&szAddress, // Буфер для считывания данных
		sizeof(szAddress), // Объём считываемых данных (в байтах)
		NULL, // Количество считанных данных (не используем)
		NULL); // Асинхронный буфер (не используем, т.к. не делали флажок FILE_FLAG_OVERLAPPED)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	printf("Success!!!\nReleasing ProcessB memory...");
	// VirtualFreeEx - Освобождает область памяти в виртуальном адресном пространстве указанного процесса
	Success = VirtualFreeEx(
		hProcessB, // Дескриптор процесса
		szAddress, // Указатель на начальный адрес области памяти, которая будет освобождена.
		0, // Размер свободной области памяти в байтах. Задаем 0, потому что ниже используем MEM_RELEASE. Функция освобождает весь регион, который зарезервирован при первоначальном вызове выделения VirtualAllocEx.
		MEM_RELEASE); // Тип операции
	/* Что вообще делает операция MEM_RELEASE?
	Освобождает указанный регион страниц или заполнитель (для заполнителя освобождается адресное пространство и доступно для других размещений). После операции страницы находятся в свободном состоянии.
    Если вы укажете это значение, dwSize должно быть 0 (ноль), а lpAddress должен указывать на базовый адрес, возвращаемый функцией VirtualAllocEx, когда регион зарезервирован. Функция не выполняется, если любое из этих условий не выполняется.
    Если какие-либо страницы в регионе фиксируются в настоящее время, функция сначала распадается, а затем освобождает их.
    Функция не завершится ошибкой, если вы попытаетесь освободить страницы, которые находятся в разных состояниях, некоторые зарезервированы, а некоторые зафиксированы. Это означает, что вы можете освободить диапазон страниц без предварительного определения текущего состояния обязательства.
    Не использутся  с MEM_DECOMMIT.*/
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	printf("Success!!!\nClosing named pipe...");
	Success = CloseHandle(hPipe); // Закрываем дескриптор канала
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	printf("Success!!!\nClosing ProcessB...");
	Success = CloseHandle(hProcessB); // Закрываем дескриптор процесса
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // Освобождаем память
		return -1;
	}

	free(str); // Освобождаем память

	printf("Success!!!\nProcessA was finished...\n");
	system("pause");
	return 0;
}

DWORD GetProcessID(char* process){
	PROCESSENTRY32 processEntry; // PROCESSENTRY32 - Описывает запись из списка процессов, находящихся в системном адресном пространстве, когда был сделан снимок.
	DWORD processID = 0; // ID процесса (пока что 0)
	HANDLE Snapshot = CreateToolhelp32Snapshot( // Делает снимок указанных процессов, а также куч, модулей и потоков, используемых этими процессами.
		TH32CS_SNAPPROCESS, // Части системы, которые будут включены в снимок. В частности, TH32CS_SNAPPROCESS - Включает все процессы в системе в моментальный снимок.
		0); // Идентификатор процесса, который будет включен в снимок. Этот параметр может быть нулем, чтобы указать текущий процесс.

	if (Snapshot != INVALID_HANDLE_VALUE) {
		processEntry.dwSize = sizeof(processEntry);
		Process32First( // Получает информацию о первом процессе, обнаруженном в системном снимке.
			Snapshot, // Дескриптор снимка, возвращенный из предыдущего вызова функции CreateToolhelp32Snapshot.
			&processEntry); // Указатель на структуру PROCESSENTRY32. Он содержит информацию о процессе, такую как имя исполняемого файла, идентификатор процесса и идентификатор процесса родительского процесса.
		// Ф-ция Process32First возвращает BOOL, но это не важно, т.к. нам главное получить нужный processEntry
		do { // Ищем нужный ID
			if (strcmp(processEntry.szExeFile, process) == 0) {
				processID = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(Snapshot, &processEntry));

		CloseHandle(Snapshot); // Закрываем дескриптор снимка
	}

	return processID;
}