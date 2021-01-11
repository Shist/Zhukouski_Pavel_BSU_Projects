#include <iostream>
#include <Windows.h>
#include <random>
#include <string>
using namespace std;

int main()
{
	system("color 0B");

	setlocale(LC_ALL, "Rus");

	random_device generator;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));

	int crime_points = 0;

	cout << "������������, ��� ������������ ������� �������." << endl;
	Sleep(500);
	cout << "��� ����������� �������� �� ��������� �������� ��� ����������� �������� ������ �����-��������." << endl;
	Sleep(500);
	cout << "� ����������� �� ����� ������� ����� ��������� ��� ����������� ������������, � ����� ��������� � ��������." << endl;
	Sleep(500);
	cout << "��� ����, ����� ����������, �������������, ������� ���� ��������� ���: ";

	string Name = "Name";
	cin >> Name;

	uniform_int_distribution<unsigned short int> distribution_name_coefficient(3, 7);
	crime_points += distribution_name_coefficient(generator)*Name.size();

	cout << "������������, " << Name << ", ��� �����������, ��������, ����������, ��� �� ��������� ��������." << endl;
	Sleep(500);
	cout << "�����������, �� ��������� � ���� ������������ ������������ � ��� ������ � ����� �������� �������� ������� " << endl;
	Sleep(500);
	cout << "�������� �����������." << endl;
	cout << "������, � �������� ������� ��� ������� ����� � ����, � ���������� ����� �������." << endl;
	Sleep(500);
	cout << "��� �� ��������� � ������ ��������?" << endl;
	cout << "������� \"1\", ���� �� �� ���������� ������ �� ������������." << endl;
	cout << "������� \"2\", ���� �� �� ������� ������ � ������� ������ ������ �������." << endl;

	string temp = "";
	int choice_num = 0;
	cin >> temp;
	choice_num = atoi(temp.c_str());

	bool first_flag = true;

	while (first_flag)
	{
		switch (choice_num)
		{
		case 1:
			first_flag = false;
			break;
		case 2:
			first_flag = false;
			crime_points += 141;
			break;
		default:
			crime_points += 25;
			cout << "��������, �� ����� ������������ ����� ��� ������, ���������� ��� ���." << endl;
			cout << "������� \"1\", ���� �� �� ���������� ������ �� ������������." << endl;
			cout << "������� \"2\", ���� �� �� ������� ������ � ������� ������ ������ �������." << endl;
			temp = "";
			cin >> temp;
			choice_num = atoi(temp.c_str());
		}
	}

	cout << "������� � ���������� �������..." << endl;
	Sleep(1500);
	cout << "�����������, �� ����� ����� �����������, ������ ��� ��������� ���������� ���, ��� " << endl;
	Sleep(500);
	cout << "����������� ������������ � ����������� �� �������� �����������, ��� ����� �� ���������� ������������." << endl;
	Sleep(500);
	cout << "������, ��� ����������, ��� ����� ��� ����� ��������� � ���������, � ������� �������� ����� ����� �����������." << endl;
	Sleep(500);
	cout << "������� �� �� ������� ����������� � ������� ���������� ��� ������ ����������� �������� ������� ����������?" << endl;
	cout << "������� \"1\", ���� �� �� ����� ����������� � ������� ����������." << endl;
	cout << "������� \"2\", ���� �� �� �� ������� �����������, ��� ����� �������� �������� ������ ����������." << endl;

	string temp_2 = "";
	int choice_num_2 = 0;
	cin >> temp_2;
	choice_num_2 = atoi(temp_2.c_str());

	bool second_flag = true;

	while (second_flag)
	{
		switch (choice_num_2)
		{
		case 1:
			second_flag = false;
			crime_points += 213;
			break;
		case 2:
			second_flag = false;
			break;
		default:
			crime_points += 25;
			cout << "��������, �� ����� ������������ ����� ��� ������, ���������� ��� ���." << endl;
			cout << "������� \"1\", ���� �� �� ����� ����������� � ������� ����������." << endl;
			cout << "������� \"2\", ���� �� �� �� ������� �����������, ��� ����� �������� �������� ������ ����������." << endl;
			temp_2 = "";
			cin >> temp_2;
			choice_num_2 = atoi(temp_2.c_str());
		}
	}

	cout << "���������� ��� �� ��������������� ������, ��������� ������ ���������� ��� " << endl;
	Sleep(500);
	cout << "����������� ������ ������������ ������������ � ������� �����-��������." << endl;
	Sleep(500);
	cout << "������ �����-��������..." << endl;
	Sleep(2700);

	uniform_int_distribution<unsigned short int> distribution(0, crime_points);

	unsigned short int crime_coefficient = distribution(generator);

	int psycho_group = 0;

	if (crime_coefficient > 0 && crime_coefficient <= 50) psycho_group = 1;
	else if (crime_coefficient > 50 && crime_coefficient <= 100) psycho_group = 2;
	else if (crime_coefficient > 100 && crime_coefficient <= 150) psycho_group = 3;
	else if (crime_coefficient > 150 && crime_coefficient <= 200) psycho_group = 4;
	else if (crime_coefficient > 200 && crime_coefficient <= 250) psycho_group = 5;
	else if (crime_coefficient > 250 && crime_coefficient <= 300) psycho_group = 6;
	else if (crime_coefficient > 300) psycho_group = 7;

	cout << "����������� ������������: ";

	switch (psycho_group)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << crime_coefficient;
		cout << "." << endl;
		cout << "��� �����-������� � �������� ���������. ��� ������������� ������ � ����� ������������ ��� ����." << endl;
		cout << "������� �� ���������� � ����� �� ������� ��������, ����� ������������." << endl;
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� �����-������� � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << "�������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " ���������. ��� ������������� �������� �� ����������� ������� �����." << endl;
		cout << "������� �� ���������� � ����� �� ������� ��������, ����� ������������." << endl;
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� �����-������� � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << "����������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " ���������. ��������� ����������� ����������. ������������ ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << "����� � ���������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "������� �� ���������� � ����� �� ������� ��������, ����� ������������." << endl;
		break;
	case 4:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� �����-������� �� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		cout << "��������� ���������� ������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ". ������ ����������� ����������. �� ������� ������ ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		cout << "�����-������������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "������� �� ���������� � ����� �� ������� ��������, ����� ������������." << endl;
		break;
	case 5:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� �����-������� � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " ���������. ��� ����� ������������� � �������� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "�������������� �����������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "� ����� � ���������������� ��� �������� �� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "���� ������������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " � ��������� �����." << endl;
		cout << "�� ���������� ���������� �������� ������� �� ����������, �����: ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "\"�����������\"";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		break;
	case 6:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� �����-������� � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "����� ������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " ���������. ��� ����� ������������� � �������� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "�������� �������������� �����������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� ��� ����� ��� ���������� ���������� ������ ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "���� ������������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ". ���� ������������ �������� �� ���� � ��������� �����." << endl;
		cout << "�� ���������� ���������� �������� ������� �� ����������, �����: ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "\"�����������\"";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		break;
	case 7:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "��� �����-������� � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "����������� ���������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ". �� - ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "������ ��� ��������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		cout << "� ����� � ������������� �� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "�� ��������� ������� ������������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "������ ������������� ������������ �����������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		cout << "�������� ������� �� ����������, �����: ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "\"������������\"";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		break;
	default:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "������� �����-�������� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "�� ����� �� �������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ", ����������� ������������ ����� ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "�������������� ��������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "����������������, �� ������� � ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "���������� �������������";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "������� �� ���������� � ����� �� ������� ��������, ����� ������������." << endl;
		break;
	}

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
	cout << "������� �������. ������� �������� ����� ������!" << endl;
	system("pause");
	return 0;
}