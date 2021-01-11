#include <windows.h>
#include <iostream>

#include "Info.h"

using namespace std;

DWORD WINAPI MarkerFunction(LPVOID);

CRITICAL_SECTION cs_console;					// Критическая секция

HANDLE* EventsFromMarker;						// Указатель на массив дескрипторов событий для подачи сигналов от экземпляров потока marker потоку main
HANDLE* EventsFromMain;							// Указатель на массив дескрипторов событий для подачи сигналов от потока main экземплярам потока marker

bool CompleteEvent;								// Флаг, с помощью которого поток main будет подавать сигнал о завершении работы

int main()
{
	setlocale(LC_ALL, "Rus");					// Подключение русского языка

	int arr_size = 0;							// Размер массива

	CompleteEvent = false;						// Флаг о завершении работы

	// Добавление данных в структуру "Данные массива"
	cout << "Введите количество элементов массива: ";
	cin >> arr_size;							// Ввод количества элементов массива с консоли
	int* arr = new int[arr_size];				// Выделяем динамическую память под массив целых чисел

	// Инициализация элементов массива нулями
	for (int i = 0; i < arr_size; i++)
		arr[i] = 0;

	int markers_num = 0;						// Количество экземпляров потока marker

	// Запрос количества потоков marker, которые требуется запустить
	cout << "Введите количество потоков marker, которые требуется запустить: ";
	cin >> markers_num;
	cout << endl;

	// Выделение динамической памяти под массив указателей на структуру "Информация", в которой содержатся все необходимые данные для работы экземпляра потока
	Info** info = new Info*[markers_num];
	for (int i = 0; i < markers_num; i++)
	{
		info[i] = new Info;									// Для каждой структуры выделяем память
		(*(info[i])).arr_size = arr_size;					// В каждой структуре указываем размер массива
		(*(info[i])).arr = arr;								// В каждой структуре вставляем в поле arr ссылку на наш массив
		(*(info[i])).thread_num = i + 1;					// В каждой структуре вставляем порядковый номер экземпляра (начиная с единицы)

		(*(info[i])).marked_elements = new bool[arr_size];	// Выделяем память под массив помеченных элементов для каждого экземпляра
		for (int j = 0; j < arr_size; j++)					// Изначально считаем, что все элементы не помеченные
			(*(info[i])).marked_elements[j] = false;
	}

	// Выделение динамиеской памяти под массив размера markers_num, который содержит указатели на экземпляры потока marker
	HANDLE* threads = new HANDLE[markers_num];

	InitializeCriticalSection(&cs_console);		// Инициализация критической секции

	// Запуск экземпляров потока marker
	for (int i = 0; i < markers_num; i++)
		threads[i] = CreateThread(				// Создание очередного экзмпляра потока marker
			NULL,								// Данный аргумент определяет, может ли создаваемый поток быть унаследован дочерним процессом
			0,									// Размер стека в байтах. Если передать 0, то будет использоваться значение по-умолчанию (1 MB)
			MarkerFunction,						// Адрес функции, которая будет выполняться потоком
			(LPVOID)info[i],					// Указатель на переменную, которая будет передана в поток.
			0,									// Флаги создания. Здесь можно отложить запуск выполнения потока. Мы будем запускать поток сразу же, передаём 0.
			NULL);								// Указатель на переменную, куда будет сохранён идентификатор потока. Нам идентификатор не нужен, передаём NULL.

	// Создание массива дескрипторов под события, с помощью которого экземпляры потока marker будут подавать сигнал потоку main
	EventsFromMarker = new HANDLE[markers_num];

	for (int i = 0; i < markers_num; i++)
	{
		char EventNum[256];						// Строка содержающая название событий для каждого экземпляра потока
		sprintf_s(EventNum, "MarkerEvent №%d", i + 1);
		EventsFromMarker[i] = CreateEvent(
			NULL,								// Атрибуты безопасности по умолчанию
			TRUE,								// Событие ручного сброса
			FALSE,								// Начальное состояние не сигнализируется
			TEXT(EventNum)						// Имя объекта
		);
	}

	// Создание массива дескрипторов под события, с помощью которого поток main будет подавать сигналы экземпляру потока marker
	EventsFromMain = new HANDLE[markers_num];

	for (int i = 0; i < markers_num; i++)
	{
		char EventNum[256];						// Строка содержающая название событий для каждого экземпляра потока
		sprintf_s(EventNum, "MainEvent №%d", i + 1);
		EventsFromMain[i] = CreateEvent(
			NULL,								// Атрибуты безопасности по умолчанию
			TRUE,								// Событие ручного сброса
			FALSE,								// Начальное состояние не сигнализируется
			TEXT(EventNum)						// Имя объекта
		);
	}

	// Это событие будет отвечать за завершение работы того или иного процесса
	CompleteEvent = (
		NULL,									// Атрибуты безопасности по умолчанию
		TRUE,									// Событие ручного сброса
		FALSE,									// Начальное состояние не сигнализируется
		TEXT("CompleteEvent")					// Имя объекта
	);

	for (int i = 0; i < markers_num; i++)
	{
		// Ждём, пока все экземпляры поток marker не сообщат о невозможности продолжения работы	
		WaitForMultipleObjects(markers_num, EventsFromMarker, TRUE, INFINITE);	// TRUE - означает, что мы ждем сигналов от КАЖДОГО потока (а не от любого из них)

		for (int j = 0; j < arr_size; j++)
			SetEvent(EventsFromMain[j]);			// Как только подтвердили сигнал от каждого потока, подаем сигнал на возобновление работы всем потокам

		EnterCriticalSection(&cs_console);			// Экземпляр потока входит в критическую секцию

		// Вывод содержимого массива на консоль
		cout << "Содержимое массива:";
		for (int j = 0; j < arr_size; j++)
			cout << " " << arr[j];
		cout << endl << endl;

		// Запрос с консоли порядкового номера экземпляра потока marker, которому будет подан сигнал на завершение своей работы
		int needed_thread_num = 0;
		cout << "Введите порядковый номер потока marker, работу которого желаете завершить: ";
		cin >> needed_thread_num;
		cout << endl;

		LeaveCriticalSection(&cs_console);			// Экземпляр потока выходит из критической секции

		CompleteEvent = true;						// Ставим флаг на завершение работы

		// Возобновление работы выбранного экземпляра потока marker
		SetEvent(EventsFromMain[needed_thread_num - 1]);						// Подаем сигнал на возобновление работы только выбранному экземпляру потока marker

		WaitForSingleObject(EventsFromMarker[needed_thread_num - 1], INFINITE);	// Ожидаем, пока выбранный экземпляр потока marker не подаст сигнал

		CompleteEvent = false;						// Возвращаем флаг о завершении работы в исходное положение

		EnterCriticalSection(&cs_console);			// Экземпляр потока входит в критическую секцию

		// Вывод содержимого массива на консоль
		cout << "Содержимое массива:";
		for (int j = 0; j < arr_size; j++)
			cout << " " << arr[j];
		cout << endl << endl;

		LeaveCriticalSection(&cs_console);			// Экземпляр потока выходит из критической секции

		for (int j = 0; j < arr_size; j++)
			SetEvent(EventsFromMain[j]);			// Подаем сигнал на возобновление работы всем потокам

		for (int j = 0; j < arr_size; j++)
			ResetEvent(EventsFromMain[j]);			// Отключаем сигнал на возобновление работы всем потокам
	}

	DeleteCriticalSection(&cs_console);				// Удаление критической секции

	// Закрываем дескрипторы все экземпляров потока marker
	for (int i = 0; i < markers_num; i++)
		CloseHandle(threads[i]);

	// Необходимо освободить динамическую память от каждого массива помеченных элементов
	for (int i = 0; i < markers_num; i++)
		delete (*(info[i])).marked_elements;

	// Необходимо освободить динамическую память от каждой структуры из массива структур
	for (int i = 0; i < markers_num; i++)
		delete info[i];

	// Закрываем дескрипторы событий для всех экземпляров потока marker
	for (int i = 0; i < markers_num; i++)
		CloseHandle(EventsFromMarker[i]);

	// Закрываем дескрипторы событий для всех экземпляров потока marker
	for (int i = 0; i < markers_num; i++)
		CloseHandle(EventsFromMain[i]);

	delete[] arr;								// Освобождаем динамическую память от массива целых чисел
	delete[] info;								// Освобождаем динамическую память от массива структур
	delete[] threads;							// Освобождаем динамическую память от массива с дескрипторами экземпляров потока marker
	delete[] EventsFromMarker;					// Освобождаем динамическую память от массива с событиями
	delete[] EventsFromMain;					// Освобождаем динамическую память от массива с событиями

	return 0;
}