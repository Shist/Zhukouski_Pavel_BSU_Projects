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
	Big_Integer(); // ����������� (�� ���������)
	virtual ~Big_Integer(); // ����������
	string Number_Output(); // ����� ����� � ���� ������
};