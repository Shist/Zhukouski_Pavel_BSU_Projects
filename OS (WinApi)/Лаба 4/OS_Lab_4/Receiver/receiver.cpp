#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

HANDLE SenderSemaphore;										// Семафор для Sender

int main()
{
	char binary_file_name[256];

	cout << "Process Receiver started work." << endl << endl;

	// Ввод данных
	cout << "Enter binary file name (for example, \"file\") : ";
	cin.getline(binary_file_name, 256);						// Ввод имени бинарного файла

	int records_num = 0;									// Количество записей
	cout << "Enter the number of records in that file: ";
	cin >> records_num;										// Ввод количества записей

	char binary_file_path[1000];							// Запомним путь до бинарного файла
	sprintf_s(binary_file_path, "%s", binary_file_name);
	ofstream f(binary_file_path, ios::binary);				// Создаём файл
	f.close();												// Закрываем до момента работы с ним

	// Ввод с консоли количества процессов Sender
	int senders_amount = 0;									// Количество процессов Sender
	cout << "Enter the number of processes Sender: ";		// Ввод количества процессов
	cin >> senders_amount;

	cin.ignore();											// Игнорируем '\n', оставшееся после ввода вышеперечисленных данных

	// Создания семафора для Sender
	SenderSemaphore = CreateSemaphore(
		NULL,												// NULL - стандартные параметры безопасности
		0,													// Инициализирующееся количество записей
		records_num,										// Максимальное количество записей
		TEXT("Sender"));									// Имя семафора

	HANDLE* EventsFromSender;								// Дескриптор указатель на массив событий для подачи сигналов от процессов sender процессу receiver

	// Создание массива дескрипторов под события, с помощью которого процессы sender будут подавать сигнал потоку main
	EventsFromSender = new HANDLE[senders_amount];
	for (int i = 0; i < senders_amount; i++)
	{
		char EventNum[256];						// Строка содержающая название событий для каждого экземпляра потока
		sprintf_s(EventNum, "Event of the process %d", (i + 1));
		EventsFromSender[i] = CreateEvent(
			NULL,								// Атрибуты безопасности по умолчанию
			TRUE,								// Событие ручного сброса
			FALSE,								// Начальное состояние не сигнализируется
			TEXT(EventNum)						// Имя объекта
		);
	}

	STARTUPINFO* Sender = new STARTUPINFO[senders_amount];	// Выделение памяти под массив процессов Sender
	PROCESS_INFORMATION* Sender_Info = new PROCESS_INFORMATION[senders_amount];	// Выделение памяти под массив структур с информацией для каждого процесса

	// Для каждого экземпляра процесса Sender создаём процесс следующим образом:
	for (int i = 0; i < senders_amount; i++)
	{
		ZeroMemory(&(Sender[i]), sizeof(Sender[i]));			// Зануление памяти (чтобы не было мусора)
		(Sender[i]).cb = sizeof(Sender[i]);						// Запоминаем размер структуры
		ZeroMemory(&(Sender_Info[i]), sizeof(Sender_Info[i]));	// Зануление памяти (чтобы не было мусора)

		char buffer[1000];

		// Передадим в аргументы командной строки имя exe-шника, имя файла, а также номер процесса
		sprintf_s(buffer, "%s %s %d", "Sender.exe", binary_file_name, (i + 1));

		CreateProcess(NULL,
			buffer,												// Аргументы командной строки для этого процесса
			NULL,
			NULL,
			FALSE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&(Sender[i]),
			&(Sender_Info[i])
		);
	}

	cout << endl << "Waiting all Sender processes to be ready for next part of work..." << endl;

	// Ждём сигнал на готовность к работе от всех процессов Sender
	WaitForMultipleObjects(senders_amount, EventsFromSender, TRUE, 1000);

	cout << "All the sender processes are ready to resume work..." << endl << endl;

	int current_records_num = 0;				// Текущее количество записей

	while (true)
	{
		if (current_records_num >= records_num)
		{
			cout << endl << "Record limit reached, process exits read mode..." << endl;
			break;										// Если мы достигли лимита записей, выходим из цикла
		}
		ifstream fin(binary_file_path, ios::binary);	// Открывает бинарный файл для чтения (1 аргумент - имя файла)
		bool file_empty = false;						// Флаг, хранящий информацию о том, пуст ли бинарный файл
		if (fin.peek() == EOF)							// Проверяем, пуст ли бинарный файл
			file_empty = true;
		fin.close();
		if (file_empty)									// Если файл пуст, то...
		{
			cout << "Binary file is empty now. Waiting for messages from Sender processes..." << endl << endl;
			while (true)
			{
				ifstream fin(binary_file_path, ios::binary);	// Открывает бинарный файл для чтения (1 аргумент - имя файла)
				if (fin.peek() != EOF)
					break;
				fin.close();
			}
		}
		cout << "There is some new message from one of the Sender processes..." << endl;
		cout << "Process Receiver: Write \"exit\" to complete work or anything else in order to read some more message from file:" << endl;
		char answer[256];						// Строка с ответом
		cin.getline(answer, 256);				// Ввод строки с консоли
		if (!strncmp(answer, "exit", 4))		// Сравниваем первые 4 символа сообщения с "exit"
			break;								// Если введён "exit", выходим из цикла
		else
		{
			char message[20];					// Строка с сообщением из файла
			ifstream fin(binary_file_path, ios::binary);	// Открывает бинарный файл для чтения (1 аргумент - имя файла)
			while (fin.peek() != EOF)
			{
				message[0] = '\0';				// Зануляем строку перед очередным сообщением
				fin.getline(message, 20);		// Чтение очередной строки из файла
				if (message[0] == '\0')			// Если новых сообщений не было, а мы попробуем что-то прочитать, то...
					cout << "There are no any new messages from Sender processes..." << endl;	// Говорим, что в файле нету новых сообщений
				else
				{
					current_records_num++;					// Инкрмент текущего количества записей
					cout << "Reading message " << current_records_num << "/" << records_num << " from binary file:" << endl;
					cout << message << endl;	// Печать сообщения из бинарного файла
				}
			}
			fin.close();
		}
		fin.close();							// Закрытие файла file.bin
		ofstream f(binary_file_path, ios::binary);	// Очищаем файл
		f.close();									// Закрываем до момента работы с ним
		cout << endl;
	}

	cout << "Process Receiver completed work." << endl;

	for (int i = 0; i < senders_amount; i++)
	{
		CloseHandle(Sender_Info[i].hProcess);				// Закрываем дескриптор очередного экземпляра процесса Sender
		CloseHandle(Sender_Info[i].hThread);				// Закрывает дескриптор очередного треда экземпляра процесса Sender
	}

	CloseHandle(SenderSemaphore);							// Закрытие семафора для Sender

	// Закрываем дескрипторы событий для всех процессов Sender
	for (int i = 0; i < senders_amount; i++)
		CloseHandle(EventsFromSender[i]);

	delete[] Sender;										// Очищение памяти от массива процессов Sender
	delete[] Sender_Info;									// Очищение памяти от массив с блоками информации о каждом процессе Sender
	delete[] EventsFromSender;								// Освобождаем динамическую память от массива с событиями от процессов Sender

	return 0;
}