#pragma once
#include <string>
#include <vector>
using namespace std;

class Big_Integer
{
private:
	const static unsigned int N = 16;
	vector<unsigned int> number[N];
public:
	Big_Integer(); // Конструктор (по умолчанию)
	virtual ~Big_Integer(); // Деструктор
	string Number_Output(); // Вывод числа в виде строки
};