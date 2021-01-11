#include <windows.h>
#include <iostream>

#include "Info.h"

using namespace std;

extern CRITICAL_SECTION cs_console;				// Критическая секция

extern HANDLE* EventsFromMarker;				// Дескриптор указатель на массив событий для подачи сигналов от экземпляров потока marker потоку main
extern HANDLE* EventsFromMain;					// Дескриптор указатель на массив событий для подачи сигналов от потока main экземплярам потока marker
extern bool CompleteEvent;						// Флаг, с помощью которого поток main будет подавать сигнал о завершении работы

// Функция min_max, записывающая минимальное и максимальное значение массива arr размера N
DWORD WINAPI MarkerFunction(LPVOID info)
{
	Info* data = (Info*)info;					// Меняем указатель LPVOID* на указатель нашей структуры

	EnterCriticalSection(&cs_console);			// Экземпляр потока входит в критическую секцию

	cout << "Экземпляр №" << (*data).thread_num << " начал свою работу." << endl << endl;

	LeaveCriticalSection(&cs_console);			// Экземпляр потока выходит из критической секции

	srand((*data).thread_num);					// Инициализация генерации последовательности случайных чисел

	int mrkd_elmnts_amount = 0;					// Количество помеченных элементов

	// Цикл с реализацией основной логики
	while (true)
	{
		int rand_num = rand();						// Генерация случайного числа
		rand_num %= (*data).arr_size;				// Деление числа по модулю на размерность массива

		EnterCriticalSection(&cs_console);			// Экземпляр потока входит в критическую секцию

		// Если элемент массива, индекс которого равен результату деления, равен нулю, то...
		if ((*data).arr[rand_num] == 0)
		{
			Sleep(5);								// Поспать 5 миллисекунд

			// Занести в элемент, индекс которого вычислен, свой порядковый номер
			(*data).arr[rand_num] = (*data).thread_num;

			LeaveCriticalSection(&cs_console);		// Экземпляр потока выходит из критической секции

			// Говорим, что этот элемент помечен экземпляром потока marker
			(*data).marked_elements[rand_num] = true;

			mrkd_elmnts_amount++;					// Инкремент количества помеченных элементов

			Sleep(5);								// Поспать 5 миллисекунд
		}
		else
		{ // В противном случае...
			cout << "Порядковый номер экземпляра потока: " << (*data).thread_num << endl;
			cout << "Количество помеченных элементов: " << mrkd_elmnts_amount << endl;
			cout << "Индекс элемента массива, который невозможно пометить: " << rand_num << endl;
			cout << "Экземпляр №" << (*data).thread_num << " подал сигнал о невозможности своей работы." << endl << endl;

			LeaveCriticalSection(&cs_console);		// Экземпляр потока выходит из критической секции

			// Помечаем, что в этом экземпляре потока marker случилось событие, подавая таким образом сигнал в поток main
			SetEvent(EventsFromMarker[(*data).thread_num - 1]);

			// Далее экземпляр потока marker ждет, пока main не разрешит ему возобновить работу
			WaitForSingleObject(EventsFromMain[(*data).thread_num - 1], INFINITE);

			// Отключаем сигнал на возобновление работы текущему потоку
			ResetEvent(EventsFromMain[(*data).thread_num - 1]);

			// Возвращаем событие в исходное положение
			ResetEvent(EventsFromMarker[(*data).thread_num - 1]);

			// Далее экземпляр потока marker ждет, пока main не разрешит ему возобновить работу
			WaitForSingleObject(EventsFromMain[(*data).thread_num - 1], INFINITE);

			EnterCriticalSection(&cs_console);	// Экземпляр потока входит в критическую секцию

			cout << "Экземпляр №" << (*data).thread_num << " возобновил свою работу." << endl << endl;

			LeaveCriticalSection(&cs_console);	// Экземпляр потока выходит из критической секции

			// Если поднят флаг на завершение работы, то экземпляр завершает свою работу
			if (CompleteEvent)
			{
				EnterCriticalSection(&cs_console);	// Экземпляр потока входит в критическую секцию

				// Заполняем нулями все помеченные ранее элементы
				for (int i = 0; i < (*data).arr_size; i++)
					if ((*data).marked_elements[i])
						(*data).arr[i] = 0;

				LeaveCriticalSection(&cs_console);	// Экземпляр потока выходит из критической секции

				break;							// И выходим из цикла
			}
		}

	}

	EnterCriticalSection(&cs_console);			// Экземпляр потока входит в критическую секцию

	cout << "Экземпляр №" << (*data).thread_num << " завершил свою работу." << endl << endl;

	LeaveCriticalSection(&cs_console);			// Экземпляр потока выходит из критической секции

	// Помечаем, что в этом экземпляре потока marker случилось событие, подавая таким образом сигнал в поток main
	SetEvent(EventsFromMarker[(*data).thread_num - 1]);

	return 0;									// Завершения работы экземпляра потока с кодом 0
}