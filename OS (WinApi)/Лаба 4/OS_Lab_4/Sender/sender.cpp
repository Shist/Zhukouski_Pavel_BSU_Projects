#include <windows.h>
#include <iostream>
#include <fstream>

#include "Queue.h"

using namespace std;

int main(int argc, char* argv[])
{
	int process_num = atoi(argv[2]);			// Номер процесса (получаем информацию о нём из командной строки)

	cout << "Process Sender " << process_num << " started work." << endl << endl;

	char EventNum[256];							// Строка содержающая название событий для каждого экземпляра потока
	sprintf_s(EventNum, "Event of the process %d", process_num);

	char binary_file_path[1000];				// Запомним путь до бинарного файла
	sprintf_s(binary_file_path, "%s", argv[1]);

	HANDLE EventFromSender = OpenEvent(
		NULL,									// Атрибуты безопасности по умолчанию
		TRUE,									// Наследование дескриптора
		TEXT(EventNum)							// Имя объекта для открытия
	);

	// Отправляем процессу Receiver сигнал на готовность к работе.
	SetEvent(EventFromSender);

	while (true)
	{
		cout << "Process Sender " << process_num << ": Waiting for the queue..." << endl;
		// Открыть семафор
		HANDLE Semaphore = OpenSemaphore(
			NULL,								// Атрибуты безопасности
			TRUE,								// Наследование дескриптора
			TEXT("Sender")						// Имя семафора
		);
		// Занять семафор
		ReleaseSemaphore(
			Semaphore,							// Дескриптор семафора
			1,									// Повышаем счетчик на единицу
			NULL								// Нам не важно запоминать прежнее значение счетчика, поэтому пишем NULL
		);
		cout << "Process Sender " << process_num << ": Write the message to the Receiver or write \"exit\" to complete work:" << endl;
		char message[20];						// Строка с сообщением
		cin.getline(message, 20);				// Ввод строки с консоли
		if (!strncmp(message, "exit", 4))		// Сравниваем первые 4 символа сообщения с "exit"
			break;								// Если введён "exit", выходим из цикла
		else
		{
			Queue MessagesQueue;				// Очередь с сообщениями
			ifstream fin(binary_file_path);		// Открываем бинарный файл, чтобы запомнить то, что было в нём изначально
			while (fin.peek() != EOF)
			{
				char* temp = new char[20];
				fin.getline(temp, 20);
				AddToQueue(&MessagesQueue, temp);
				delete[] temp;
			}
			fin.close();
			ofstream fout(binary_file_path);	// Открывает бинарный файл для записи
			while (!QueueIsEmpty(&MessagesQueue))
			{
				fout << MessagesQueue.first->msg << endl;
				DeleteFromQueue(&MessagesQueue);
			}
			fout << message << endl;
			cout << "Message from Process Sender " << process_num << " successfully sent" << endl;
			fout.close();						// Закрытие бинарного файла
		}
		cout << endl;
	}

	cout << "Process Sender " << process_num << " completed work." << endl;

	CloseHandle(EventFromSender);				// Закрываем дескриптор события

	return 0;
}