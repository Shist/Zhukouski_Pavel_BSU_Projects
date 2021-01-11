#include <windows.h>
#include <iostream>

#include "Info.h"

using namespace std;

DWORD WINAPI MarkerFunction(LPVOID);

CRITICAL_SECTION cs_console;					// ����������� ������

HANDLE* EventsFromMarker;						// ��������� �� ������ ������������ ������� ��� ������ �������� �� ����������� ������ marker ������ main
HANDLE* EventsFromMain;							// ��������� �� ������ ������������ ������� ��� ������ �������� �� ������ main ����������� ������ marker

bool CompleteEvent;								// ����, � ������� �������� ����� main ����� �������� ������ � ���������� ������

int main()
{
	setlocale(LC_ALL, "Rus");					// ����������� �������� �����

	int arr_size = 0;							// ������ �������

	CompleteEvent = false;						// ���� � ���������� ������

	// ���������� ������ � ��������� "������ �������"
	cout << "������� ���������� ��������� �������: ";
	cin >> arr_size;							// ���� ���������� ��������� ������� � �������
	int* arr = new int[arr_size];				// �������� ������������ ������ ��� ������ ����� �����

	// ������������� ��������� ������� ������
	for (int i = 0; i < arr_size; i++)
		arr[i] = 0;

	int markers_num = 0;						// ���������� ����������� ������ marker

	// ������ ���������� ������� marker, ������� ��������� ���������
	cout << "������� ���������� ������� marker, ������� ��������� ���������: ";
	cin >> markers_num;
	cout << endl;

	// ��������� ������������ ������ ��� ������ ���������� �� ��������� "����������", � ������� ���������� ��� ����������� ������ ��� ������ ���������� ������
	Info** info = new Info*[markers_num];
	for (int i = 0; i < markers_num; i++)
	{
		info[i] = new Info;									// ��� ������ ��������� �������� ������
		(*(info[i])).arr_size = arr_size;					// � ������ ��������� ��������� ������ �������
		(*(info[i])).arr = arr;								// � ������ ��������� ��������� � ���� arr ������ �� ��� ������
		(*(info[i])).thread_num = i + 1;					// � ������ ��������� ��������� ���������� ����� ���������� (������� � �������)

		(*(info[i])).marked_elements = new bool[arr_size];	// �������� ������ ��� ������ ���������� ��������� ��� ������� ����������
		for (int j = 0; j < arr_size; j++)					// ���������� �������, ��� ��� �������� �� ����������
			(*(info[i])).marked_elements[j] = false;
	}

	// ��������� ����������� ������ ��� ������ ������� markers_num, ������� �������� ��������� �� ���������� ������ marker
	HANDLE* threads = new HANDLE[markers_num];

	InitializeCriticalSection(&cs_console);		// ������������� ����������� ������

	// ������ ����������� ������ marker
	for (int i = 0; i < markers_num; i++)
		threads[i] = CreateThread(				// �������� ���������� ��������� ������ marker
			NULL,								// ������ �������� ����������, ����� �� ����������� ����� ���� ����������� �������� ���������
			0,									// ������ ����� � ������. ���� �������� 0, �� ����� �������������� �������� ��-��������� (1 MB)
			MarkerFunction,						// ����� �������, ������� ����� ����������� �������
			(LPVOID)info[i],					// ��������� �� ����������, ������� ����� �������� � �����.
			0,									// ����� ��������. ����� ����� �������� ������ ���������� ������. �� ����� ��������� ����� ����� ��, ������� 0.
			NULL);								// ��������� �� ����������, ���� ����� ������� ������������� ������. ��� ������������� �� �����, ������� NULL.

	// �������� ������� ������������ ��� �������, � ������� �������� ���������� ������ marker ����� �������� ������ ������ main
	EventsFromMarker = new HANDLE[markers_num];

	for (int i = 0; i < markers_num; i++)
	{
		char EventNum[256];						// ������ ����������� �������� ������� ��� ������� ���������� ������
		sprintf_s(EventNum, "MarkerEvent �%d", i + 1);
		EventsFromMarker[i] = CreateEvent(
			NULL,								// �������� ������������ �� ���������
			TRUE,								// ������� ������� ������
			FALSE,								// ��������� ��������� �� ���������������
			TEXT(EventNum)						// ��� �������
		);
	}

	// �������� ������� ������������ ��� �������, � ������� �������� ����� main ����� �������� ������� ���������� ������ marker
	EventsFromMain = new HANDLE[markers_num];

	for (int i = 0; i < markers_num; i++)
	{
		char EventNum[256];						// ������ ����������� �������� ������� ��� ������� ���������� ������
		sprintf_s(EventNum, "MainEvent �%d", i + 1);
		EventsFromMain[i] = CreateEvent(
			NULL,								// �������� ������������ �� ���������
			TRUE,								// ������� ������� ������
			FALSE,								// ��������� ��������� �� ���������������
			TEXT(EventNum)						// ��� �������
		);
	}

	// ��� ������� ����� �������� �� ���������� ������ ���� ��� ����� ��������
	CompleteEvent = (
		NULL,									// �������� ������������ �� ���������
		TRUE,									// ������� ������� ������
		FALSE,									// ��������� ��������� �� ���������������
		TEXT("CompleteEvent")					// ��� �������
	);

	for (int i = 0; i < markers_num; i++)
	{
		// ���, ���� ��� ���������� ����� marker �� ������� � ������������� ����������� ������	
		WaitForMultipleObjects(markers_num, EventsFromMarker, TRUE, INFINITE);	// TRUE - ��������, ��� �� ���� �������� �� ������� ������ (� �� �� ������ �� ���)

		for (int j = 0; j < arr_size; j++)
			SetEvent(EventsFromMain[j]);			// ��� ������ ����������� ������ �� ������� ������, ������ ������ �� ������������� ������ ���� �������

		EnterCriticalSection(&cs_console);			// ��������� ������ ������ � ����������� ������

		// ����� ����������� ������� �� �������
		cout << "���������� �������:";
		for (int j = 0; j < arr_size; j++)
			cout << " " << arr[j];
		cout << endl << endl;

		// ������ � ������� ����������� ������ ���������� ������ marker, �������� ����� ����� ������ �� ���������� ����� ������
		int needed_thread_num = 0;
		cout << "������� ���������� ����� ������ marker, ������ �������� ������� ���������: ";
		cin >> needed_thread_num;
		cout << endl;

		LeaveCriticalSection(&cs_console);			// ��������� ������ ������� �� ����������� ������

		CompleteEvent = true;						// ������ ���� �� ���������� ������

		// ������������� ������ ���������� ���������� ������ marker
		SetEvent(EventsFromMain[needed_thread_num - 1]);						// ������ ������ �� ������������� ������ ������ ���������� ���������� ������ marker

		WaitForSingleObject(EventsFromMarker[needed_thread_num - 1], INFINITE);	// �������, ���� ��������� ��������� ������ marker �� ������ ������

		CompleteEvent = false;						// ���������� ���� � ���������� ������ � �������� ���������

		EnterCriticalSection(&cs_console);			// ��������� ������ ������ � ����������� ������

		// ����� ����������� ������� �� �������
		cout << "���������� �������:";
		for (int j = 0; j < arr_size; j++)
			cout << " " << arr[j];
		cout << endl << endl;

		LeaveCriticalSection(&cs_console);			// ��������� ������ ������� �� ����������� ������

		for (int j = 0; j < arr_size; j++)
			SetEvent(EventsFromMain[j]);			// ������ ������ �� ������������� ������ ���� �������

		for (int j = 0; j < arr_size; j++)
			ResetEvent(EventsFromMain[j]);			// ��������� ������ �� ������������� ������ ���� �������
	}

	DeleteCriticalSection(&cs_console);				// �������� ����������� ������

	// ��������� ����������� ��� ����������� ������ marker
	for (int i = 0; i < markers_num; i++)
		CloseHandle(threads[i]);

	// ���������� ���������� ������������ ������ �� ������� ������� ���������� ���������
	for (int i = 0; i < markers_num; i++)
		delete (*(info[i])).marked_elements;

	// ���������� ���������� ������������ ������ �� ������ ��������� �� ������� ��������
	for (int i = 0; i < markers_num; i++)
		delete info[i];

	// ��������� ����������� ������� ��� ���� ����������� ������ marker
	for (int i = 0; i < markers_num; i++)
		CloseHandle(EventsFromMarker[i]);

	// ��������� ����������� ������� ��� ���� ����������� ������ marker
	for (int i = 0; i < markers_num; i++)
		CloseHandle(EventsFromMain[i]);

	delete[] arr;								// ����������� ������������ ������ �� ������� ����� �����
	delete[] info;								// ����������� ������������ ������ �� ������� ��������
	delete[] threads;							// ����������� ������������ ������ �� ������� � ������������� ����������� ������ marker
	delete[] EventsFromMarker;					// ����������� ������������ ������ �� ������� � ���������
	delete[] EventsFromMain;					// ����������� ������������ ������ �� ������� � ���������

	return 0;
}