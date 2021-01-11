#pragma once
#include "Soft_Drinks.h"

enum class Taste
{ // ���� ��������
	Lemon,
	Strawberry,
	Raspberry,
	Plum,
	Coke
};

class Lemonade :
	public Soft_Drinks // ��������� �� ������ "�������������� �������"
{
private:
	Taste tast;
public:
	Lemonade(string, int, int, Taste); // ����������� ��� �������� (��������, ����� � ��, ���� ��������, ���)
	virtual ~Lemonade(); // ����������� ����������
	string get_name() const; // ������ (���������� �������� ��������)
	int get_volume() const; // ������ (���������� ����� ��������)
	int get_exp_date() const; // ������ (���������� ���������� � ����� �������� � ����)
	void set_exp_date(int); // ������ ��� ��������� ���������� � ���������� ����� �������� ���� ��� ����� �������
	Taste get_tast() const; // ������ (���������� ���� ��������)
};