#include <iostream>
using namespace std;

const int CharHalfSize = CHAR_MIN;

int main()
{
	setlocale(LC_ALL, "Rus");
	char AgressionLevel = 1 + CharHalfSize;
	cout << "������� �������� ����� �� ����, ��� �� ������ ����������: " << AgressionLevel - CharHalfSize << "/255\n";
	AgressionLevel -= 2;
	cout << "������� �������� ����� ����� ����, ��� �� ������ ����������: " << AgressionLevel - CharHalfSize << "/255" << endl;
	return 0;
}