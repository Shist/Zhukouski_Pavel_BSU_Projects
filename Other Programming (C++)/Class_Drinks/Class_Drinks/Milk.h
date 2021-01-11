#pragma once
#include "Soft_Drinks.h"

class Milk :
	public Soft_Drinks // ��������� �� ������ "�������������� �������"
{
private:
	double fat_perc;  // ����, ��������� ���������� � ���������� �������� � ������ (� ���������)
public:
	Milk(string, int, double, int); // ����������� ��� ������ (��������, ����� � ��, ������� ��������, ���� ��������)
	virtual ~Milk(); // ����������� ����������
	string get_name() const; // ������ (���������� �������� ������)
	int get_volume() const; // ������ (���������� ����� ������ � ��)
	double get_fat_perc() const; // ������ (���������� ������� �������� � ������)
	int get_exp_date() const; // ������ (���������� ���������� � ����� �������� � ����)
	void set_exp_date(int); // ������ ��� ��������� ���������� � ���������� ����� �������� ���� ��� ����� �������
};