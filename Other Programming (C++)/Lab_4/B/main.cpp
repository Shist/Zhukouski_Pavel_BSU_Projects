#include <iostream>
#pragma warning(disable: 4996) // ��������� ������������ �����������

using namespace std;

const int MAXLENGTH = 300; // ������ ��������� ��� ����, ����� ������ ����������� ������

bool isInStr(const char *str, int c) // ������ ������� isInStr, ����� � �� ������� ������� ������� strtok
{
	int i = 0;
	do
	{
		if (str[i] == c) return true;
		i++;
	} while (str[i - 1] != '\0');
	return false;
}

char *strtok(char *str, const char *delim) // ������ ������� strtok, ������� ���������� ��� � �������� ����� ��������� 
{
	static char *curr_pos, preview;
	if (str != NULL)
	{
		curr_pos = str;
		preview = '\0';
	}
	char *startToken;
	int i = 0;
	if (*curr_pos == '\0' && preview == '\0') return NULL;
	else if (*curr_pos == '\0') curr_pos++;
	while ((curr_pos[i] != '\0') && (isInStr(delim, curr_pos[i]))) i++;
	if (curr_pos == '\0')
	{
		curr_pos = NULL;
		return NULL;
	}
	startToken = curr_pos + i;
	while (!isInStr(delim, curr_pos[i])) i++;
	curr_pos += i;
	preview = *curr_pos;
	*curr_pos = '\0';
	return startToken;
}

char *strcpy(char *p, const char *v) // ������ ����� ������� strcpy, ����� ��������� ������� �������� � �������� ���������
{
	char *st = p;
	while (*v)
		*(p++) = *(v++);
	++(*p) = '\0';
	return st;
}

int main()
{
	char *str = new char[MAXLENGTH + 1]; // �������� ������ ��� ���� ������
	cout << "Enter string:\n"; // ���� ������
	cin.getline(str, MAXLENGTH + 1); // ������ � ������� ���� ������ (�� ����� 300 ��������)
	char *pos = strtok(str, " "); // ������ �������, ������� ���� ������� � ����� ������
	char *word = new char[MAXLENGTH + 1]; // �������� ������ ��� ��������������� ������ word, � ������� �� ����� ������� ���������
	int distinct, minDistinct = MAXLENGTH + 1; // ������ ��������� ����������, ������� ����������� � �������� ���������
	bool have[256]; // ������ bool-������ ��� 256 ���������, ������� ����� ������� ���������� � ���, ���������� �� ��� �����-�� ������ � ������
	while (pos != NULL)
	{ // ����� ���������� ��������, ������� ������������ ���������� ��������� �������� ��� ������� ����� � ������
		distinct = 0; 
		for (int i = 0; i < 256; i++)
			have[i] = false; // �������������� ������ ������� ������� bool ��� false
		for (int i = 0; pos[i] != '\0'; i++) // ���������� ��� ������� � �����
			if (!have[pos[i] - '\0']) // �������� �� ��, ���������� �� ��� ���� ������ ������
			{
				have[pos[i] - '\0'] = true; // �������, ��� ������ pos[i] ��� ����������
				distinct++;
			}
		if (distinct < minDistinct)
		{
			minDistinct = distinct;
			strcpy(word, pos); // ��� ����������� �������� ����������� ������� word �������� ������� pos, ���������� ������ � ����������� ����������� ��������
		}
		pos = strtok(NULL, " ");
	}
	cout << "Your required word is:\n";
	cout << word << endl;
	delete []str; // ����������� ������
	delete []word; // ���������� ������
	return 0;
}