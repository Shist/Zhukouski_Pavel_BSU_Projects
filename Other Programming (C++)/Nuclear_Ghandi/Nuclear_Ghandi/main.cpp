#include <iostream>
using namespace std;

const int CharHalfSize = CHAR_MIN;

int main()
{
	setlocale(LC_ALL, "Rus");
	char AgressionLevel = 1 + CharHalfSize;
	cout << "Уровень агрессии Ганди ДО того, как он принял демократию: " << AgressionLevel - CharHalfSize << "/255\n";
	AgressionLevel -= 2;
	cout << "Уровень агрессии Ганди ПОСЛЕ того, как он принял демократию: " << AgressionLevel - CharHalfSize << "/255" << endl;
	return 0;
}