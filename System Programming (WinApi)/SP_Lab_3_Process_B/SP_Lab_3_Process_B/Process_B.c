#include <windows.h>
#include <stdio.h>

int main(void)
{
	//-----------------------------���������� ���� ����������-----------------------------

	LPCTSTR pipename = "\\\\.\\pipe\\MyPipe"; // ��� ������
	HANDLE hNamedPipe; // ���������� ������������ ������
	DWORD szAddress; // ����� ���������� ������
	char* msg; // ���������� ������
	BOOL Success; // ���� ��������� ��������/����������/������

	//------------------------------------------------------------------------------------

	printf("Creating named pipe...");
	// CreateNamedPipe - ������� ��������� ������������ ������ � ���������� ���������� ��� ����������� �������� ������.
	// ��������� ������� ������������ ������ ���������� ��� ������� ���� ��� �������� ������� ���������� ������������� ������������ ������ �
	// ��������� ��� �������� ���������, ���� ��� �������� ������ ���������� ������������� ������������ ������.
	hNamedPipe = CreateNamedPipe( // ������� ����������� �����
		pipename, // ��� ������
		PIPE_ACCESS_DUPLEX, // ����� ���������������; ��������� � ���������� �������� ����� ������ � ������ � ���������� � ����
		PIPE_TYPE_MESSAGE | // ������ ������������ � ����� � ����������� �� ���� ��� ����� ���������
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT, // �������������� �������� � ������� ���������� �������� ���������� ���������
		PIPE_UNLIMITED_INSTANCES, // ������������ ����� �����������
		sizeof(DWORD), // ������ ��� ���������� ������
		sizeof(DWORD), // ������ ��� ��������� ������
		NULL, // ������������ �������� time-out �� ��������� (�� ������������)
		NULL); // �������� ������
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nConnecting to pipe...");
	ConnectNamedPipe( // ��������� ������� ������������ ������ �����, ���� ���������� ������� ����������� � ���������� ������������ ������.
		hNamedPipe, // ���������� ������
		NULL); // ��������� �� ���������� ��������� (�� �����)

	printf("Success!!!\nReading from pipe...");
	Success = ReadFile( // ��������� ��, ��� ������� A ������� ��� � ������ (�����, �� �������� �������� ������)
		hNamedPipe, // ��� ������������ ������
		&szAddress, // ����� ��� ����������
		sizeof(szAddress), // ����� ����������� ������ (� ������)
		NULL, // ���������� ��������� ������ (�� ����������)
		NULL); // ����������� ����� (�� ����������)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nYour string: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg); // printf_s - ������� ������. %s - ������ ��������

	printf("Sending answer to ProccessA...");
	Success = WriteFile( // ������� �������� A, ��� �� �������� ����� ������ � ��� ��� ����� ������� ������
		hNamedPipe, // ���������� ������ 
		&szAddress, // ������ ��� ������ 
		sizeof(szAddress), // ����� ������������ ������
		NULL, // ���������� ���������� ������ (�� ����������)
		NULL); // ����������� ����� (�� ����������)
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nDisconnecting from named pipe...");
	Success = DisconnectNamedPipe(hNamedPipe); // ����������� �� ����������� ������
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nClosing named pipe...");
	Success = CloseHandle(hNamedPipe); // ��������� ���������� ������
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nProcessB was finished...\n");
	system("pause");
	return 0;
}