#include <windows.h>
#include <stdio.h>

int main(void)
{
	//-----------------------------объявление всех переменных-----------------------------

	LPCTSTR pipename = "\\\\.\\pipe\\MyPipe"; // Имя канала
	HANDLE hNamedPipe; // Дескриптор именованного канала
	DWORD szAddress; // Адрес выделенной памяти
	char* msg; // Получаемая строка
	BOOL Success; // Флаг успешного открытия/считывания/записи

	//------------------------------------------------------------------------------------

	printf("Creating named pipe...");
	// CreateNamedPipe - Создает экземпляр именованного канала и возвращает дескриптор для последующих операций канала.
	// Серверный процесс именованного канала использует эту функцию либо для создания первого экземпляра определенного именованного канала и
	// установки его основных атрибутов, либо для создания нового экземпляра существующего именованного канала.
	hNamedPipe = CreateNamedPipe( // Создаем Именованный канал
		pipename, // Имя канала
		PIPE_ACCESS_DUPLEX, // Канал двунаправленный; серверные и клиентские процессы могут читать с канала и записывать в него
		PIPE_TYPE_MESSAGE | // Данные записываются в канал и считываются из него как поток сообщений
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT, // Неограниченное ожидание в течение выполнения действий клиентским процессом
		PIPE_UNLIMITED_INSTANCES, // Максимальное число экземпляров
		sizeof(DWORD), // Резерв для выводимого буфера
		sizeof(DWORD), // Резерв для вводимого буфера
		NULL, // Спецификатор значения time-out по умолчанию (не используется)
		NULL); // Атрибуты защиты
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nConnecting to pipe...");
	ConnectNamedPipe( // Позволяет серверу именованного канала ждать, пока клиентский процесс подключится к экземпляру именованного канала.
		hNamedPipe, // Дескриптор канала
		NULL); // Указатель на перекрытую структуру (не нужно)

	printf("Success!!!\nReading from pipe...");
	Success = ReadFile( // Считываем то, что процесс A прислал нам в канале (адрес, по которому хранится строка)
		hNamedPipe, // Имя именованного канала
		&szAddress, // Буфер для считывания
		sizeof(szAddress), // Объём считываемых данных (в байтах)
		NULL, // Количество считанных данных (не используем)
		NULL); // Ссинхронный буфер (не используем)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nYour string: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg); // printf_s - выводит строку. %s - Строка символов

	printf("Sending answer to ProccessA...");
	Success = WriteFile( // Сказали процессу A, что мы получили адрес строки и что уже можно очищать память
		hNamedPipe, // Дескриптор канала 
		&szAddress, // Данные для записи 
		sizeof(szAddress), // Объём записываемых данных
		NULL, // Количество записанных данных (не используем)
		NULL); // Асинхронный буфер (не используем)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nDisconnecting from named pipe...");
	Success = DisconnectNamedPipe(hNamedPipe); // Отключаемся от дескриптора канала
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nClosing named pipe...");
	Success = CloseHandle(hNamedPipe); // Закрываем дескриптор канала
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nProcessB was finished...\n");
	system("pause");
	return 0;
}