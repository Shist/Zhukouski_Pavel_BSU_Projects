#include <windows.h>
#include <iostream>

#include "ArrData.h"

using namespace std;

// ����������
extern double sum;									// ����������, �������� ����� ���� ��������� �������
extern double avrg;									// ������� �������������� �������� ������� (�� ��������� ����� 0.0)

extern CRITICAL_SECTION cs_console;					// ����������� ������

// ������� average, ������������ ������� �������������� �������� ��������� ������� arr ������� N
DWORD WINAPI AverageFunction(LPVOID ad)
{
	EnterCriticalSection(&cs_console);				// ����� ������ � ����������� ������

	cout << "����� Average ����� ���� ������\n\n";

	LeaveCriticalSection(&cs_console);				// ����� ������� �� ����������� ������

	ArrData* data = (ArrData*)ad;					// ������ ��������� LPVOID* �� ��������� ����� ���������
	sum = 0.0;										// ����������, �������� ����� ���� ��������� �������
	avrg = 0.0;										// ������� �������������� �������� ������� (�� ��������� ����� 0.0)

	// ������ ����� ���� ��������� �������
	for (int i = 0; i < (*data).N; i++)
	{
		EnterCriticalSection(&cs_console);			// ����� ������ � ����������� ������

		sum += (*data).arr[i];

		LeaveCriticalSection(&cs_console);			// ����� ������� �� ����������� ������

		Sleep(12);									// ����� ������ �������� ������������ ����� ���� 12 �����������	
	}

	avrg = (double)sum / (*data).N;					// ������ �������� ���������������

	EnterCriticalSection(&cs_console);				// ����� ������ � ����������� ������

	// ����� ���������� � ������� �������������� �� �������
	cout << "������� �������������� ���� ��������� �������: " << avrg << "\n\n";

	cout << "����� Average �������� ���� ������\n\n";

	LeaveCriticalSection(&cs_console);				// ����� ������� �� ����������� ������

	return 0;
}