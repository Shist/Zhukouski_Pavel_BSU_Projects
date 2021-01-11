#include <windows.h>
#include <iostream>

#include "ArrData.h"

using namespace std;

// Переменные
extern double sum;									// Переменная, хранящая сумму всех элементов массива
extern double avrg;									// Среднее арифметическое значение массива (по умолчанию равно 0.0)

extern CRITICAL_SECTION cs_console;					// Критическая секция

// Функция average, записывающая среднее арифметическое значение элементов массива arr размера N
DWORD WINAPI AverageFunction(LPVOID ad)
{
	EnterCriticalSection(&cs_console);				// Поток входит в критическую секцию

	cout << "Поток Average начал свою работу\n\n";

	LeaveCriticalSection(&cs_console);				// Поток выходит из критической секции

	ArrData* data = (ArrData*)ad;					// Меняем указатель LPVOID* на указатель нашей структуры
	sum = 0.0;										// Переменная, хранящая сумму всех элементов массива
	avrg = 0.0;										// Среднее арифметическое значение массива (по умолчанию равно 0.0)

	// Расчет суммы всех элементов массива
	for (int i = 0; i < (*data).N; i++)
	{
		EnterCriticalSection(&cs_console);			// Поток входит в критическую секцию

		sum += (*data).arr[i];

		LeaveCriticalSection(&cs_console);			// Поток выходит из критической секции

		Sleep(12);									// После каждой операции суммирования поток спит 12 миллисекунд	
	}

	avrg = (double)sum / (*data).N;					// Расчет среднего арифметического

	EnterCriticalSection(&cs_console);				// Поток входит в критическую секцию

	// Вывод информации о среднем арифметическом на консоль
	cout << "Среднее арифметическое всех элементов массива: " << avrg << "\n\n";

	cout << "Поток Average закончил свою работу\n\n";

	LeaveCriticalSection(&cs_console);				// Поток выходит из критической секции

	return 0;
}