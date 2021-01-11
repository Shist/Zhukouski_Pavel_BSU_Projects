#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

// ��������� ������� �����, ������� �������� � �������
struct employee
{
	int num;			// ����������������� ����� ����������
	char name[10];		// ��� ����������
	double hours;		// ���������� ������������ �����
};

int main()
{
	char binary_file_name[256];

	// ���� ������
	cout << "Enter binary file name: ";
	cin.getline(binary_file_name, 256);						// ���� ����� ��������� �����
	int records_num = 0;									// ���������� �������
	cout << "Enter the number of records in that file: ";
	cin >> records_num;										// ���� ���������� �������
	cin.ignore();											// ����������� ���� ������

	STARTUPINFO Creator;
	ZeroMemory(&Creator, sizeof(Creator));					// ��������� ������ (����� �� ���� ������)
	Creator.cb = sizeof(Creator);							// ���������� ������ ���������
	PROCESS_INFORMATION Creator_Info;
	ZeroMemory(&Creator_Info, sizeof(Creator_Info));		// ��������� ������ (����� �� ���� ������)
	char buffer[1000];
	sprintf_s(buffer, "%s %s %d", "OS_Lab_1_Creator.exe", binary_file_name, records_num);

	CreateProcess(NULL,
		buffer,				// ��������� ��������� ������ ��� ����� ��������
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&Creator,
		&Creator_Info
	);

	WaitForSingleObject(Creator_Info.hProcess, INFINITE);			// ����, ���� Creator �������� ���� ������

	CloseHandle(Creator_Info.hProcess);								// ��������� ���������� �������� Creator
	CloseHandle(Creator_Info.hThread);								// ��������� ���������� ����� Creator

	cout << "Information, written to binary file:" << endl;
	buffer[0] = '\0';
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", binary_file_name);
	ifstream fin(buffer, ios::binary);
	fin.read((char*)&records_num, sizeof(int));						// ��������� ���������� � ���������� ����������� �� ��������� �����
	employee* records = new employee[records_num];

	// ���� ���������� �������� ����� �� �����������, ������ ���������� � ��������� ������...
	for (int i = 0; i < records_num; i++)
	{
		fin.read((char*)&records[i], sizeof(employee));
	}

	cout << records[0].num << " " << records[0].name << " " << records[0].hours;			// ����� ��� ���-�� �����
	for (int i = 1; i < records_num; i++)													// ������� ������� ������, ����� endl ��������� � ����, ����� � ����� �� ���� ������ ������ ������
		cout << endl << records[i].num << " " << records[i].name << " " << records[i].hours;

	delete[] records;

	fin.close();

	char output_file_name[256];
	cout << "\n\nEnter output file name: ";
	cin.getline(output_file_name, 256);									// ���� ����� ��������� �����
	double salary_per_hour = 0.0;										// �������� �� ��� ������
	cout << "Enter salary value per one hour: ";
	cin >> salary_per_hour;												// ��������� �������� �� ��� ������
	buffer[0] = '\0';
	sprintf_s(buffer, "%s %s %s %lf", "OS_Lab_1_Reporter.exe", binary_file_name, output_file_name, salary_per_hour);

	STARTUPINFO Reporter;
	ZeroMemory(&Reporter, sizeof(Reporter));							// ��������� ������ (����� �� ���� ������)
	Reporter.cb = sizeof(Reporter);										// ���������� ������ ���������
	PROCESS_INFORMATION Reporter_Info;
	ZeroMemory(&Reporter_Info, sizeof(Reporter_Info));					// ��������� ������ (����� �� ���� ������)
	CreateProcess(NULL,
		buffer,															// ��������� ��������� ������ ��� ����� ��������
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&Reporter,
		&Reporter_Info
	);
	WaitForSingleObject(Reporter_Info.hProcess, INFINITE);				// ����, ���� Creator �������� ���� ������
	CloseHandle(Reporter_Info.hProcess);								// ��������� ���������� �������� Reporter
	CloseHandle(Reporter_Info.hThread);									// ��������� ���������� ����� Reporter
	buffer[0] = '\0';
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", output_file_name);
	ifstream fin_ReportInfo(buffer);
	cout << endl << "Information, read from output file:" << endl;

	// ���� ���������� �������� ����� �� �����������, ������ ���������� � ��������� ������...
	for (int i = 0; i < records_num; i++)
	{
		buffer[0] = '\0';
		fin_ReportInfo.getline(buffer, 1000);
		for (int i = 0; buffer[i] != '\0'; i++)
			printf("%c", buffer[i]);
		cout << endl;
	}
	fin_ReportInfo.close();
	return 0;
}