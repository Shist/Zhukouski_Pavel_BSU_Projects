#include <iostream>
#pragma warning(disable: 4996) // ��������� ������������ �����������
using namespace std;

char *strcat(char *strDestination, const char *strSource) // ����������� ���������� ����������� ������� strcat
{
	int endPos = 0, i = 0;
	while (strDestination[endPos] != '\0') // ���� ������, ��� ������� ����������� ����� ������ ������
	{
		endPos++;
	}
	while (strSource[i] != '\0') // ���� ������, ��� ������� ����������� ����� ������ ������, �� ���������, ������ ���������:
	{
		strDestination[endPos+i] = strSource[i]; // ��������� ������� �� ������ ������ � ����� ������ ������
		i++;
	}
	strDestination[endPos + i] = '\0';
	return strDestination; // ���������� �������� ������ ������
}
int main() // �������� ����� ���������
{
	char *arr1 = new char[301]; // �������� ������ ��� ������ ������, ������� ������ � �������
	char *arr2 = new char[301]; // �������� ������ ��� ������ ������, ������� ������ � �������
	cout << "Enter the first line:\n";
	cin.getline(arr1, 301); // ������ �������� 1-�� ������ � �������
	cout << "Enter the second line you want to connect with the first:\n";
	cin.getline(arr2, 301); // ������ �������� 2-�� ������ � �������
	strcat(arr1, arr2); // ����� �������
	cout << "The resulting line is the next:\n";
	cout << arr1 << endl; // ����� ������������ ������
	delete []arr1; // ����������� ������
	delete []arr2; // ����������� ������
	return 0;
}