#pragma once // ������������� ������, ��������� � ��������� ��������� ������
#include <iostream>
#include <exception>
using namespace std;

class Fraction
{
private: // � ��������� ������� ������ ��� ������ ��� ����������, ����� ����� � ���� ��������...
	long ch;
	long zn;
	void reduction(); // �������, ������� ����� ��������� ���� �����
public:
	Fraction(); // ����������� �� ���������
	Fraction(long long, long long); // ����������� ��� ����� ������
	virtual ~Fraction(); // ����������� ����������

	long get_ch() const; // ��� ��������� ���������� � ���������
	void set_ch(long long); // ��� ��������� ���������� � ���������

	long get_zn() const; // ��� ��������� ���������� � �����������
	void set_zn(long long); // ��� ��������� ���������� � �����������

	Fraction operator + (const Fraction&) const; // ��������
	Fraction operator - (const Fraction&) const; // ���������
	Fraction operator - () const; // ��������� ����� (������� �����)
	Fraction operator * (const Fraction &) const; // ���������
	Fraction operator / (const Fraction &) const; // �������
	 // ���� ����������� �������� ���������
	bool operator < (const Fraction&) const;
	bool operator > (const Fraction&) const;
	bool operator <= (const Fraction&) const;
	bool operator >= (const Fraction&) const;
	bool operator == (const Fraction&) const;
	bool operator != (const Fraction&) const;

	double SeeDouble() const; // ������� ��� ������ ����� � ������� double

	friend ostream & operator << (ostream &, const Fraction &); // �������, ������ ��� ���������� ������
};