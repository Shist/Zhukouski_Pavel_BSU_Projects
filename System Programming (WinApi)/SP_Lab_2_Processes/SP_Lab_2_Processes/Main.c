#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

// BOOL - ������ bool (NULL ��� 1)
// DWORD - 32-������ ����������� �����. �������: unsigned long int, UINT.
BOOL GetProcessList();
BOOL ListProcessModules(DWORD dwPID);
BOOL ListProcessThreads(DWORD dwOwnerPID);

int main()
{
	GetProcessList(); // ������ �������� �������� ����� (�� �����, ���� ����, ���������� ��� ��������� ������)
	return 0;
}

BOOL GetProcessList()
{ // ����� "�������� ������ ���������"
	HANDLE hProcessSnap; // HANDLE - ���������� �������
	HANDLE hProcess;
	PROCESSENTRY32 pe32; // ���� � ������ ���������
	// PROCESSENTRY32 - ��������� ������ �� ������ ���������, ����������� � ��������� �������� ������������, �� ��������. (��� ����� ���������)
	DWORD dwPriorityClass;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// C������ ������� ���������� ���������, ������� � �.�.
	// �������� dwFlags ����������, ������� ���� ������ �� ����� ��������. (������ 0x00000002)
	// �������� dwProcessId ������ ������������� ��������, ��� �������� ��������� �������. (������ 0)
	// ���������� ����� ��������

	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return(FALSE); // ���� � ������������ ��������� ���-�� �� ���, �� ���������� 0 � ������

	pe32.dwSize = sizeof(PROCESSENTRY32); // sizeof ���������� ���������� ������, ������� �������� processentry32
	// dwSize - ��� ���� �� ����� ��������� ���� PROCESSENTRY23

	if (!Process32First(hProcessSnap, &pe32))
	{ // Process32First - �������� ���������� � ������ ��������, ������������ � ��������� ������.
		CloseHandle(hProcessSnap); // ���� ������ �� �����, ��������� ������� ����������� �...
		return(FALSE); // ���������� 0 � ������
	}
	// Process32First ��������� �����, ���������� �� CreateToolhelp32Snapshot, 
	// ��������� � dwFlags = TH32CS_SNAPPROCESS, � ����� ��������� �� ��������� PROCESSENTRY32. 
	// ����� ������� ��������� ���� dwSize ���� ��������� ������ ���� ����������� � sizeof(PROCESSENTRY32). 
	// � ������ ������ ������������ TRUE, � � peProcessEntry ������������ ���������� � ������ ��������

	do
	{
		_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile); // �������� ��� ������� (��� ����� �� ������ �� ����� ��������� pe32)

		dwPriorityClass = 0;
		// OpenProcess(...) - ��������� ������������ ������ ���������� ��������.
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); // ������� �������

		if (hProcess == INVALID_HANDLE_VALUE)
			return(FALSE); // ���� ���-�� ����� �� ���, ���������� 0

		dwPriorityClass = GetPriorityClass(hProcess);
		// GetPriorityClass ��������� �������� ������ ���������� ��� ��������� �������� hProcess.
		// ��� ��������, ������ �� ��������� ���������� ������� ������ ��������, ������������� �������� ������� ���������� ������� ������.
		CloseHandle(hProcess);
		// ����� �������� ���������� � ��������
		_tprintf(TEXT("\n  Process ID        = %d"), pe32.th32ProcessID); // ID ��������
		_tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads); // ���-�� ������ � ��
		_tprintf(TEXT("\n  Parent process ID = %d"), pe32.th32ParentProcessID); // ID ��������, ������� ������ ���� ������� (������������ �������)
		_tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase); // ������� ��������� ����� �������, ��������� ���� ���������

		ListProcessModules(pe32.th32ProcessID); // ����������� ��� ������ ������� �������� (���� ����)
		ListProcessThreads(pe32.th32ProcessID); // ����������� ��� ����� ������� �������� (���� ����)

	} while (Process32Next(hProcessSnap, &pe32)); // �� �� �����, ��� � Process32First, ������ ��� ���������
	CloseHandle(hProcessSnap); // ���������
	return(TRUE);
}

BOOL ListProcessModules(DWORD dwPID) // �������� ID �������� ��������
{ // ������ - exe-�����, dll-��, � �.�. (���������������� ���)
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32; // MODULEENTRY32 - ���������, �������� ��� ������������ ������� � �������� ��������

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	// CreateToolhelp32Snapshot - ������ ������ ��������� ���������, � ����� ���, ������� � �������, ������������ ����� ����������.
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return(FALSE); // ���� ���-�� ����� �� ���, ���������� 0

	me32.dwSize = sizeof(MODULEENTRY32); // ������ ���� dwSuze ������ ��������� tagMODULEENTRY32W

	if (!Module32First(hModuleSnap, &me32))
	{ // Module32First - �� �� �����, ��� Process32First, ������ � ��������, � �� ����������
		CloseHandle(hModuleSnap);
		return(FALSE);
	}
	do
	{ // �������� ���������� � ������...
		_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule); // ��� ������
		_tprintf(TEXT("\n     Path     = %s"), me32.szExePath); // ���� � ������
		_tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID); // ID ��������, � ������� ���� ������ �������������
		_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize); // ������ ������ (� ������)

	} while (Module32Next(hModuleSnap, &me32)); // �� �� �����, ��� � Module32First, ������ ��� ���������
	CloseHandle(hModuleSnap); // ���������
	return(TRUE);
}

BOOL ListProcessThreads(DWORD dwOwnerPID) // �������� ID �������� ��������
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32; // THREADENTRY32 - ���������, �������� ��� ������������ ������ � �������� ��������

	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	// CreateToolhelp32Snapshot - ������ ������ ��������� ���������, � ����� ���, ������� � �������, ������������ ����� ����������.
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE); // ���� ���-�� ����� �� ���, ���������� 0

	te32.dwSize = sizeof(THREADENTRY32); // ������ ���� dwSuze ������ ��������� tagTHREADENTRY32

	if (!Thread32First(hThreadSnap, &te32))
	{// Thread32First - �� �� �����, ��� Module32First, ������ � ��������
		CloseHandle(hThreadSnap);
		return(FALSE);
	}
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{ // ���� ID-���� ����� ��������� � ID-������ �������, �� �������� ���������� � ��
			_tprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID); // ID-���� �����
			_tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri); // ������� ������� ���������� ����, ����������� ������.
			// ��������� - ��� ����� �� 0 �� 31, ��� 0 ������������ ���������� ��������� ��������� ������.
			_tprintf(TEXT("\n     Delta priority = %d"), te32.tpDeltaPri); // ���� ������� ������ �� ������������ � ������ ��������������� � ����.
			_tprintf(TEXT("\n"));
		}
	} while (Thread32Next(hThreadSnap, &te32)); // �� �� �����, ��� � Thread32First, ������ ��� ���������
	CloseHandle(hThreadSnap); // ���������
	return(TRUE);
}