#include <iostream>
#include <fstream>
using namespace std;

struct employee
{					// ��������� ������� �����, ������� �������� � �������
	int num;		// ����������������� ����� ����������
	char name[10];	// ��� ����������
	double hours;	// ���������� ������������ �����
};

// �� ����� ��������� (��� �����) (���-�� �������)
int main(int argc, char* argv[])
{
	char buffer[1000];
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", argv[1]);
	ofstream fout(buffer, ios::binary);		// ������� �������� ���� (1 �������� � ������� - ��� �����)

	int records_num = atoi(argv[2]);		// 2-�� �������� � ������� - ���������� ������� (atoi(str) - ���������� ������ str � ����� �����) 
	employee* records = new employee[records_num];

	cout << endl << "So, now enter information about all the " << records_num << " employees:" << endl << endl;
	for (int i = 0; i < records_num; i++)
	{
		cout << "Employee number " << (i + 1) << ": ";
		cin >> records[i].num;
		cin >> records[i].name;
		cin >> records[i].hours;
		cout << endl;
	}

	// ����� ���������� � ������ ���������� � �������� ����:
	fout.write((char*)&records_num, sizeof(int));	// ������� ���������� �����������
	for (int i = 0; i < records_num; i++)			// ������� ������� ������, ����� endl ��������� � ����, ����� � ����� �� ���� ������ ������ ������
		fout.write((char*)&records[i], sizeof(employee));

	fout.close();

	delete[] records;

	return 0;
}