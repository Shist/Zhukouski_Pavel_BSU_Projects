#pragma once // ������������� ������, ��������� � ��������� ��������� ������
#include <iostream>
#include <exception>
using namespace std;

class Money
{
private:
	long long sum; // � ���� ���������� ����� ������� �����, ������ pd * sh * 2 * p
	bool check = false; // ������ ������, ������� ����� ��������� set-������, ��� ��� ����������� sum
public:
	Money(); // ����������� ��� ���������� (������ ������� �����)
	Money(int, int, double); // ����������� � ����� �����������, ������� ������ 3 ���������� (�������� ������)
	virtual ~Money(); // ����������� ����������
	long long get_sum() const; // ��� ��������� ���������� � �����
	void set_sum(int, int, double, long long); // ��� ��������� ���������� � �����
	Money operator + (const Money&) const; // ��������
	Money operator - (const Money&) const; // ���������
	Money operator - () const; // ������� �����
	Money operator += (const Money& x); // �������� � �����������
	Money operator -= (const Money& x); // ��������� � �����������
	bool operator == (const Money&) const; // ��������� (�����)
	friend ostream& operator << (ostream& s, const Money& x);
};