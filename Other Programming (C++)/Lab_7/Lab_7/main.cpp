#include <iostream>
#include <fstream>
#include <cstring> // ���������� cstring ��� ������� strlen � strcpy
#pragma warning (disable: 4996) // ��������� ������������ �����������
using namespace std;

bool check = false;
fstream open_file(const char *prompt, char *file_name, ios_base::openmode mode)
{ // ������ �������, � ������� ������� ����� ������� ���������� ���� � ��������� �����
	cout << prompt << '\n'; // � ��������� prompt ����� ������� (� ����� ��������) ��������� ������������
	char *new_name = new char[256]; // �������� ������ ��� ������ �������� ��� ����� ������
	new_name[0] = '\0'; // �������� ������
	cin.getline(new_name, 256);
	if (strlen(new_name) != 0) // ���� ����� ����� ����� �� ����� ����, ��...
	{
		strcpy(file_name + '.' + 't' + 'x' + 't', new_name); // ����������� �������� ������ ��� ��� ����� + ��������� ���������� .txt
	}
	delete[] new_name; // ������� ������ �� �������
	return fstream(file_name, mode);
}

int main()
{
	char* file_name = new char[256]; // �������� ������ ��� ������ �������� ��� ����� ������
	strcpy(file_name, "IN.TXT"); // � ������� ������� strcpy ������� � file_name �������� IN.TXT
	fstream fin = open_file("Enter file name in which you store input data...\n"
		"If you enter nothing then file named IN.txt will be opened", 
		file_name, ios_base::in); // ������� ���������� ���� ��� �����, ������� ����� ������...
	if (fin.is_open()) // ���� ���� �����������, ��������� ���������...
	{
		if (fin.peek() == EOF) // ��������� ���� �� �������
		{
			cerr << "File IN.TXT is empty!";
			return 2;
		}
		strcpy(file_name, "OUT.TXT"); // � ������� ������� strcpy ������� � file_name �������� OUT.TXT
		fstream fout = open_file("Enter file name in which you want to store the result of calculations...\n"
			"If you enter nothing then file name will be OUT.txt",
			file_name, ios_base::out); // ������� ���������� ���� ��� �����, � ������� ����� �������� ����������...
		int str_num = 1; // � ���� ���������� ����� ������� ����� ������� � �����
		int kol_vo = 0; // � ���� ���������� ����� ������� ���������� ���������� ������ �������
		int group_num = 0; // � ���� ���������� ����� ������� ����� ������
		bool str_empty = true; // ������ ������, � ������� ����� ������� ���������� � ���, �������� �� ������ ������
		char symbol; // ������ ��� ����������, ����� ������ �������
		while ((symbol = fin.get()) != EOF) // ���� ���������� ����� �� �����������, ������ ���������...
		{
			if (symbol != '\n') // ���� ������ �� �������� ������������ �� ����� �������, �� ������ ���������...
			{
				if (symbol != ' ') // ���� ������ �� �������� ��������, �� ������ ���������...
				{
					str_empty = false; // �������, ��� ��� ������ �� ������
					if (kol_vo != 0) // ���� �� ���� ������� ���� ������ �������, �� ������ ���������...
					{
						group_num++; // ������ ��������� ������ ������, �.�. �� ������� ����� ������
						fout << "The " << group_num << " group: " <<
							kol_vo << " repetitions, the line number of the beginning of the group is " << str_num - kol_vo<< endl;
					}
					kol_vo = 0; // �������� ���������� ������ ����� �� ����� ������
				}
			}
			else // ���� �� ������ �������� ������������ �� ����� �������, �� ������ ���, ���...
			{
				if (str_empty) // ���� ��� ������� ���� ������, ��...
				{
					kol_vo++; // �������� ���������� ������ ������� �� �������
				}
				str_num++; // �.�. �� ������� �� ����� ������, �� ������ ��������� ������ ������
				str_empty = true; // ��� ����� ������� ������ ������ ������� �� true
			}
		}
		if (str_empty) kol_vo++; // ���� ��������� ������� ���� �������, �� ������ ��������� ���������� kol_vo
		if (kol_vo != 0) // ���� ��� �����, ��� ��������� ������� (�������) � ����� ��������� (���������) ������ (�������), ��
		{
			group_num++; // ������ ��������� ������ ������, �.�. �� ������� ����� ������
			fout << "The " << group_num << " group: " <<
				kol_vo << " repetitions, the line number of the beginning of the group is " << str_num - kol_vo + 1 << endl;
		}
		if (group_num == 0) // ���������, ���� �� ������ ������ � ����� ����� ������
		{
			fout << "There are no any empty lines in file!" << endl;
		}
		fin.close(); // ��������� �������� ���� 
		fout.close(); // �������� ��������� ����
	}
	else
	{
		cerr << "Input file did not open!";
		return 1;
	}
	delete[] file_name; // ������� ������ �� �������
	return 0;
}