#include <windows.h>
#include <stdio.h>

int main(void) {

	//-----------------------------объявление всех переменных-----------------------------

	LPCTSTR pipename = "\\\\.\\pipe\\mynamedpipe";					// имя канала
	HANDLE hNamedPipe;												// дескриптор именованного канала
	DWORD szAddress;												// адрес выделенной памяти
	DWORD cbRead, cbWritten;										// буфферы (имеют промежуточное значение)
	char* msg;														// получаемая строка
	BOOL Success;													// флаг успешного открытия/считывания/записи

	//------------------------------------------------------------------------------------

	printf("Creating named pipe...");
	hNamedPipe = CreateNamedPipe(
		pipename,													// имя канала
		PIPE_ACCESS_DUPLEX,											// канал двунаправленный; серверные и клиентские процессы могут читать с канала и записывать в него
		PIPE_TYPE_MESSAGE |											// данные записываются в канал и считываются из него как поток сообщений
		PIPE_READMODE_MESSAGE |	
		PIPE_WAIT,													// неограниченное ожидание в течение выполнения действий клиентским процессом
		PIPE_UNLIMITED_INSTANCES,									// максимальное число экземпляров
		sizeof(DWORD),												// резерв для выводимого буфера
		sizeof(DWORD),												// резерв для вводимого буфера
		100,														// спецификатор значения time-out по умолчанию (не используется)
		NULL);														// атрибуты защиты
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nConnecting to pipe...");
	ConnectNamedPipe(hNamedPipe, NULL);

	printf("Success!!!\nReading from pipe...");
	Success = ReadFile(
		hNamedPipe,													// имя именованного канала
		&szAddress,													// буфер для считывания
		sizeof(szAddress),											// объём считываемых данных
		&cbRead,													// количество считанных данных (не используем)
		NULL);														// асинхронный буфер (не используем)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nYour string: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg);

	printf("Sending answer to ProccessA...");
	Success = WriteFile(
		hNamedPipe,													// дескриптор канала 
		&szAddress,													// данные для записи 
		sizeof(szAddress),											// объём записываемых данных
		&cbWritten,													// количество записанных данных (не используем)
		NULL);														// асинхронный буфер (не используем)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nDisconnecting from named pipe...");
	Success = DisconnectNamedPipe(hNamedPipe);
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nClosing named pipe...");
	Success = CloseHandle(hNamedPipe);
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nProcessB was finished...\n");
	system("pause");
	return 0;
}