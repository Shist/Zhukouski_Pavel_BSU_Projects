#include <windows.h>
#include <iostream>

#include "Info.h"

using namespace std;

extern CRITICAL_SECTION cs_console;				// ����������� ������

extern HANDLE* EventsFromMarker;				// ���������� ��������� �� ������ ������� ��� ������ �������� �� ����������� ������ marker ������ main
extern HANDLE* EventsFromMain;					// ���������� ��������� �� ������ ������� ��� ������ �������� �� ������ main ����������� ������ marker
extern bool CompleteEvent;						// ����, � ������� �������� ����� main ����� �������� ������ � ���������� ������

// ������� min_max, ������������ ����������� � ������������ �������� ������� arr ������� N
DWORD WINAPI MarkerFunction(LPVOID info)
{
	Info* data = (Info*)info;					// ������ ��������� LPVOID* �� ��������� ����� ���������

	EnterCriticalSection(&cs_console);			// ��������� ������ ������ � ����������� ������

	cout << "��������� �" << (*data).thread_num << " ����� ���� ������." << endl << endl;

	LeaveCriticalSection(&cs_console);			// ��������� ������ ������� �� ����������� ������

	srand((*data).thread_num);					// ������������� ��������� ������������������ ��������� �����

	int mrkd_elmnts_amount = 0;					// ���������� ���������� ���������

	// ���� � ����������� �������� ������
	while (true)
	{
		int rand_num = rand();						// ��������� ���������� �����
		rand_num %= (*data).arr_size;				// ������� ����� �� ������ �� ����������� �������

		EnterCriticalSection(&cs_console);			// ��������� ������ ������ � ����������� ������

		// ���� ������� �������, ������ �������� ����� ���������� �������, ����� ����, ��...
		if ((*data).arr[rand_num] == 0)
		{
			Sleep(5);								// ������� 5 �����������

			// ������� � �������, ������ �������� ��������, ���� ���������� �����
			(*data).arr[rand_num] = (*data).thread_num;

			LeaveCriticalSection(&cs_console);		// ��������� ������ ������� �� ����������� ������

			// �������, ��� ���� ������� ������� ����������� ������ marker
			(*data).marked_elements[rand_num] = true;

			mrkd_elmnts_amount++;					// ��������� ���������� ���������� ���������

			Sleep(5);								// ������� 5 �����������
		}
		else
		{ // � ��������� ������...
			cout << "���������� ����� ���������� ������: " << (*data).thread_num << endl;
			cout << "���������� ���������� ���������: " << mrkd_elmnts_amount << endl;
			cout << "������ �������� �������, ������� ���������� ��������: " << rand_num << endl;
			cout << "��������� �" << (*data).thread_num << " ����� ������ � ������������� ����� ������." << endl << endl;

			LeaveCriticalSection(&cs_console);		// ��������� ������ ������� �� ����������� ������

			// ��������, ��� � ���� ���������� ������ marker ��������� �������, ������� ����� ������� ������ � ����� main
			SetEvent(EventsFromMarker[(*data).thread_num - 1]);

			// ����� ��������� ������ marker ����, ���� main �� �������� ��� ����������� ������
			WaitForSingleObject(EventsFromMain[(*data).thread_num - 1], INFINITE);

			// ��������� ������ �� ������������� ������ �������� ������
			ResetEvent(EventsFromMain[(*data).thread_num - 1]);

			// ���������� ������� � �������� ���������
			ResetEvent(EventsFromMarker[(*data).thread_num - 1]);

			// ����� ��������� ������ marker ����, ���� main �� �������� ��� ����������� ������
			WaitForSingleObject(EventsFromMain[(*data).thread_num - 1], INFINITE);

			EnterCriticalSection(&cs_console);	// ��������� ������ ������ � ����������� ������

			cout << "��������� �" << (*data).thread_num << " ���������� ���� ������." << endl << endl;

			LeaveCriticalSection(&cs_console);	// ��������� ������ ������� �� ����������� ������

			// ���� ������ ���� �� ���������� ������, �� ��������� ��������� ���� ������
			if (CompleteEvent)
			{
				EnterCriticalSection(&cs_console);	// ��������� ������ ������ � ����������� ������

				// ��������� ������ ��� ���������� ����� ��������
				for (int i = 0; i < (*data).arr_size; i++)
					if ((*data).marked_elements[i])
						(*data).arr[i] = 0;

				LeaveCriticalSection(&cs_console);	// ��������� ������ ������� �� ����������� ������

				break;							// � ������� �� �����
			}
		}

	}

	EnterCriticalSection(&cs_console);			// ��������� ������ ������ � ����������� ������

	cout << "��������� �" << (*data).thread_num << " �������� ���� ������." << endl << endl;

	LeaveCriticalSection(&cs_console);			// ��������� ������ ������� �� ����������� ������

	// ��������, ��� � ���� ���������� ������ marker ��������� �������, ������� ����� ������� ������ � ����� main
	SetEvent(EventsFromMarker[(*data).thread_num - 1]);

	return 0;									// ���������� ������ ���������� ������ � ����� 0
}