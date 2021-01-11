#pragma once
#include "Soft_Drinks.h"

enum class Carbonated
{
	Still,
	Sparkled
};

class Mineral_Water :
	public Soft_Drinks // ��������� �� ������ "�������������� �������"
{
private:
	Carbonated carb;
public:
	Mineral_Water(string, int, int, Carbonated); // ����������� ��� ��������� (��������, ����� � ��, ���� ��������)
	virtual ~Mineral_Water(); // ����������� ����������
	string get_name() const; // ������ (���������� �������� ���������)
	int get_volume() const; // ������ (���������� ����� ���������)
	int get_exp_date() const; // ������ (���������� ���������� � ����� �������� � ����)
	void set_exp_date(int); // ������ ��� ��������� ���������� � ���������� ����� �������� ���� ��� ����� �������
	Carbonated get_carb() const; // ������ (���������� ��� ���������)
};