#include <windows.h>
#include <iostream>
using namespace std;

struct employee
{
	char full_name[50];
	int depart_number;
	char job_post[30];
	int job_start_date;
};

int main(int argc, char* argv[])
{
	printf_s("Process Daughter started his work...\n\n");	// ���������� ������������, ��� ������ ������� ����� ���� ������

	printf_s("Process Daughter got the next command line: \"%s %s\"\n\n", argv[0], argv[1]);	// ������� �� ��, ��� ���� �������� ����� ��������� ������

	int struct_to_change = atoi(argv[1]);					// ��������� �� ��������� ������ 1-�� �������� � ���������� ��� �� ������ � ����� �����

	printf_s("So, you're going to change information about structure number \"%d\".\n\n", struct_to_change);	// ����� ��� ������������

	employee new_object;									// ��������� � ����� ��������, ������� �� ������� � ���� ��������

	printf_s("Enter new full name for structure number \"%d\": ", struct_to_change);
	scanf_s("%s", &(new_object.full_name), (unsigned)_countof(new_object.full_name));

	printf_s("Enter new department number for structure number \"%d\": ", struct_to_change);
	scanf_s("%d", &(new_object.depart_number));

	printf_s("Enter new job post for structure number \"%d\": ", struct_to_change);
	scanf_s("%s", &(new_object.job_post), (unsigned)_countof(new_object.job_post));

	printf_s("Enter new job start date for structure number \"%d\": ", struct_to_change);
	scanf_s("%d", &(new_object.job_start_date));

	LPCWSTR fn = L"File_New.dat";							// ������ � ������ �����, ��� ��� ���������� �������

	// ���������� ���������� �����
	HANDLE File = CreateFile(
		fn,													// ��� �����
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	employee object;										// ����������, � ������� ����� �������� ��������� � ����� �����������
	DWORD n;												// �������, � ������� �������� �� ������, ��� ����� �� ����� �����
	int curr_struct_num = 0;								// ����� ����������, ������� � ��� ��������

	// ������ ������ �� ����� ��� �������� �� ����������
	while (ReadFile(File, &object, sizeof(object), &n, NULL) && n != 0)
		curr_struct_num++;									// ������������ ���������� ��������

	employee* objects = new employee[curr_struct_num];		// ������� ������ �� curr_struct_num ��������

	SetFilePointer(File, 0, 0, FILE_BEGIN);					// ���������� ����� �� ������ �����

	int i = 0;												// �������

	while (ReadFile(File, &objects[i], sizeof(object), &n, NULL) && n != 0)
	{
		if (struct_to_change == (i + 1))
		{ // ���� ����� ��������� ������������� ���� ������, ��� �� ��������, �� ������ ����� ���������� � ������ ��� ���������
			strcpy_s(objects[i].full_name, new_object.full_name);	// �������� ����� �������� ����� � ������
			objects[i].depart_number = new_object.depart_number;	// �������� ����� �������� ������ ������������ � ������
			strcpy_s(objects[i].job_post, new_object.job_post);		// �������� ����� �������� ������� ��������� � ������
			objects[i].job_start_date = new_object.job_start_date;	// �������� ����� �������� ���� ������ ������ � ������
		}
		i++;												// ���������� ��� ������ �� ������� ����� � ������
	}

	CloseHandle(File);										// ��������� ���������� �����

	// ������ ���������� ����� ��� ���������� (���. CREATE_ALWAYS)
	File = CreateFile(
		fn,													// ��� �����
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS, // ���������� �����
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	for (int i = 0; i < curr_struct_num; i++) // ������ ����� ������ � ����
		WriteFile(File, &objects[i], sizeof(employee), &n, NULL);

	CloseHandle(File);										// ��������� ���������� �����

	delete[] objects;										// ������� ������ �� ������� ��������

	return 0;
}