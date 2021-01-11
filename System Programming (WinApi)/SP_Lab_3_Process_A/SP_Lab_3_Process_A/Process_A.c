#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>

#define MAXLENGTH 101 // ����� ������ ������ ������ (101 = 100 �������� + '\0')
DWORD GetProcessID(char*);// ������� ��������� ID ��������
// DWORD - 32-������ ����������� �����. �������: unsigned long int, UINT.

int main(void)
{
	//-----------------------------���������� ���� ����������-----------------------------

	LPCTSTR pipename = "\\\\.\\pipe\\MyPipe"; // ��� ������
	// LPCTSTR � ��������� �� ����������� ������, ��� UNICODE.  �� ����� long pointer constant TCHAR string. ��� ���������� ������� LPCSTR.
	HANDLE hProcessB; // ���������� �������� B
	LPVOID szAddress; // ����� � ������ �������� B (LPVOID - ��������� �� ����� ���)
	DWORD dBuf;	// ������ (����� ������������� ��������, DWORD - ������ Unsigned INT32)
	BOOL Success; // ���� ��������� ��������/����������/������
	DWORD szSize = sizeof(char) * MAXLENGTH; // ������ �������� ������
	char* str = (char*)malloc(szSize); // ���� ������
	HANDLE hPipe = INVALID_HANDLE_VALUE; // ���������� ������

	//------------------------------------------------------------------------------------

	printf("Enter your string: ");
	gets_s(str, MAXLENGTH - 1); // ���� ������ (get_s - �������� ������ str �� ������ stdin, ������ ������ MAXLENGTH - 1)

	printf("Opening ProcessB...");
	hProcessB = OpenProcess(
		PROCESS_ALL_ACCESS, // ������������� ������� ������� � ������� ��������
		FALSE, // �������� ����������� ������������ (false - ���������� �� ����� ����������� ����������)
		GetProcessID("SP_Lab_3_Process_B.exe")); // ID �������� (� ������ ������ - �������� B)
	if (hProcessB == INVALID_HANDLE_VALUE)
	{
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	printf("Success!!!\nAllocating memory for ProcessB...");
	// VirtualAllocEx - �����������, ��������� ��� �������� ��������� ������� ������ � ����������� �������� ������������
	// ���������� ��������. ������� �������������� ������, ���������� ����.
	/*���� ������� ����������� �������, ������������ �������� �������� ������� ������� ���������� ������� �������.
	���� ������� �� ��������, ������������ �������� ����� NULL.*/
	szAddress = VirtualAllocEx( // � �������� ������������ �������� B �������� ������
		hProcessB, // ���������� �������� (� ������ ������ - �������� B)
		0, // ���� �������� ������? ��� ��� �� ����� 0, ������� ���� ������, ��� ��������
		szSize, // ����� ������������� ������
		MEM_RESERVE | // ��������������� ��������
		MEM_COMMIT, // �������� ���������� ������
		PAGE_EXECUTE_READWRITE); // ������� ������
	/*������� ������������� ������������ �������� ������� ����� �������� MEM_COMMIT ��� MEM_RESERVE � ���������� lpAddress ����������� ��������, 
	���� ���� �������� ��� �� ��������������. ���������� ��� ������ - ERROR_INVALID_ADDRESS.*/

	printf("Success!!!\nWriting your string in ProcessB memory...");
	Success = WriteProcessMemory( // ���������� ������ � ������� ������ � ��������� ��������. ��� ������� ��� ������ ������ ���� ��������, ����� �������� ���������� ��������.
		hProcessB, // ���������� �������� (� ������ ������ - �������� B)
		szAddress, // ���� ����������
		str, // ��� ����������
		szSize, // ����� ������������ ������
		0); // ��������� �� ����������, ������� �������� ����� ������, ���������� � ��������� ������� (������������, ���� 0)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	printf("Success!!!\nConnecting to named pipe...");
	while (hPipe == INVALID_HANDLE_VALUE) {
		hPipe = CreateFile( // ������������ � ���� ������������ ������, ��� ������� � �������� B
			pipename, // ��� ������������ ������ (�����)
			GENERIC_READ | // ������� ������ � ������ � ������
			GENERIC_WRITE,
			0, // ��� ����������� ������� (������ �� ����� ��������� ��������������, � �� ����� ���� ������ ����� �� ��� ���, ���� ���������� �� ���������)
			NULL, // ��� ������������ ������
			OPEN_EXISTING, // ��������� ������������ �����
			0, // �������� ����� �� ���������
			NULL); // ��� ����������� ����� �������
	}

	printf("Success!!!\nWriting memory address...");
	dBuf = (DWORD)szAddress; // ��������� ������ ������ � �����
	Success = WriteFile( // ���������� � ����������� ����� �����, � ������� �������� ������
		hPipe, // ���������� ������ (�����)
		&dBuf, // ������ ��� ������ (� ������ ������ - ����� ������ � �������� B) 
		sizeof(dBuf), // ����� ������������ ������ (� ������)
		NULL, // ���������� ���������� ������ (�� ����������)
		NULL); // ����������� ����� (�� ����������)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	printf("Success!!!\nWaiting answer from ProcessB...");
	Success = ReadFile( // �������� ����� �� �������� B, ��� �� ������� ����� ������
		hPipe, // ��� ������������ ������ (���������� �����)
		&szAddress, // ����� ��� ���������� ������
		sizeof(szAddress), // ����� ����������� ������ (� ������)
		NULL, // ���������� ��������� ������ (�� ����������)
		NULL); // ����������� ����� (�� ����������, �.�. �� ������ ������ FILE_FLAG_OVERLAPPED)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	printf("Success!!!\nReleasing ProcessB memory...");
	// VirtualFreeEx - ����������� ������� ������ � ����������� �������� ������������ ���������� ��������
	Success = VirtualFreeEx(
		hProcessB, // ���������� ��������
		szAddress, // ��������� �� ��������� ����� ������� ������, ������� ����� �����������.
		0, // ������ ��������� ������� ������ � ������. ������ 0, ������ ��� ���� ���������� MEM_RELEASE. ������� ����������� ���� ������, ������� �������������� ��� �������������� ������ ��������� VirtualAllocEx.
		MEM_RELEASE); // ��� ��������
	/* ��� ������ ������ �������� MEM_RELEASE?
	����������� ��������� ������ ������� ��� ����������� (��� ����������� ������������� �������� ������������ � �������� ��� ������ ����������). ����� �������� �������� ��������� � ��������� ���������.
    ���� �� ������� ��� ��������, dwSize ������ ���� 0 (����), � lpAddress ������ ��������� �� ������� �����, ������������ �������� VirtualAllocEx, ����� ������ ��������������. ������� �� �����������, ���� ����� �� ���� ������� �� �����������.
    ���� �����-���� �������� � ������� ����������� � ��������� �����, ������� ������� �����������, � ����� ����������� ��.
    ������� �� ���������� �������, ���� �� ����������� ���������� ��������, ������� ��������� � ������ ����������, ��������� ���������������, � ��������� �������������. ��� ��������, ��� �� ������ ���������� �������� ������� ��� ���������������� ����������� �������� ��������� �������������.
    �� �����������  � MEM_DECOMMIT.*/
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	printf("Success!!!\nClosing named pipe...");
	Success = CloseHandle(hPipe); // ��������� ���������� ������
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	printf("Success!!!\nClosing ProcessB...");
	Success = CloseHandle(hProcessB); // ��������� ���������� ��������
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		free(str); // ����������� ������
		return -1;
	}

	free(str); // ����������� ������

	printf("Success!!!\nProcessA was finished...\n");
	system("pause");
	return 0;
}

DWORD GetProcessID(char* process){
	PROCESSENTRY32 processEntry; // PROCESSENTRY32 - ��������� ������ �� ������ ���������, ����������� � ��������� �������� ������������, ����� ��� ������ ������.
	DWORD processID = 0; // ID �������� (���� ��� 0)
	HANDLE Snapshot = CreateToolhelp32Snapshot( // ������ ������ ��������� ���������, � ����� ���, ������� � �������, ������������ ����� ����������.
		TH32CS_SNAPPROCESS, // ����� �������, ������� ����� �������� � ������. � ���������, TH32CS_SNAPPROCESS - �������� ��� �������� � ������� � ������������ ������.
		0); // ������������� ��������, ������� ����� ������� � ������. ���� �������� ����� ���� �����, ����� ������� ������� �������.

	if (Snapshot != INVALID_HANDLE_VALUE) {
		processEntry.dwSize = sizeof(processEntry);
		Process32First( // �������� ���������� � ������ ��������, ������������ � ��������� ������.
			Snapshot, // ���������� ������, ������������ �� ����������� ������ ������� CreateToolhelp32Snapshot.
			&processEntry); // ��������� �� ��������� PROCESSENTRY32. �� �������� ���������� � ��������, ����� ��� ��� ������������ �����, ������������� �������� � ������������� �������� ������������� ��������.
		// �-��� Process32First ���������� BOOL, �� ��� �� �����, �.�. ��� ������� �������� ������ processEntry
		do { // ���� ������ ID
			if (strcmp(processEntry.szExeFile, process) == 0) {
				processID = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(Snapshot, &processEntry));

		CloseHandle(Snapshot); // ��������� ���������� ������
	}

	return processID;
}