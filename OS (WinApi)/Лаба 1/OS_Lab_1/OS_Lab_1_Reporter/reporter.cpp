#include <fstream>
using namespace std;

struct employee
{					// ��������� ������� �����, ������� �������� � �������
	int num;		// ����������������� ����� ����������
	char name[10];	// ��� ����������
	double hours;	// ���������� ������������ �����
};

// ��������� ����������
struct employee_sal
{
	int num;		// ����������������� ����� ����������
	char name[10];	// ��� ����������
	double hours;	// ���������� ������������ �����
	double salary;	// ��������
};

// �� ����� ��������� (��� ��������� ��������� �����) (��� ����� ������) (������ �� ��� ������)
int main(int argc, char* argv[])
{
	char buffer[1000];
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", argv[1]);
	ifstream fin(buffer, ios::binary);					// ��������� �������� ���� (1 �������� � ������� - ��� ��������� ��������� �����)

	buffer[0] = '\0';
	sprintf_s(buffer, "%s%s", "C:\\Users\\user\\source\\repos\\OS_Lab_1\\Debug\\", argv[2]);
	ofstream fout(buffer);								// ������� ��������� ���� (2 �������� � ������� - ��� �����)

	double salary_per_hour = atof(argv[3]);				// ������ �� ��� ������ (atoi(str) - ���������� ������ str � ������� �����)
	int records_num = 0;
	fin.read((char*)&records_num, sizeof(int));			// ��������� ���������� � ���������� �����������
	employee_sal* records = new employee_sal[records_num];

	// ���� ���������� �������� ����� �� �����������, ������ ���������� � ��������� ������...
	for (int i = 0; i < records_num; i++)
	{
		employee temp;
		fin.read((char*)&temp, sizeof(employee));
		records[i].num = temp.num;
		strcpy_s(records[i].name, temp.name);
		records[i].hours = temp.hours;
		records[i].salary = salary_per_hour * records[i].hours;
	}

	fout << records[0].num << " " << records[0].name << " " << records[0].hours << " " << records[0].salary;				// ����� ��� ���-�� ����� ��������
	for (int i = 1; i < records_num; i++)																					// ������� ������� ������, ����� endl ��������� � ����, ����� � ����� �� ���� ������ ������ ������
		fout << endl << records[i].num << " " << records[i].name << " " << records[i].hours << " " << records[i].salary;

	fin.close();
	fout.close();

	delete[] records;

	return 0;
}