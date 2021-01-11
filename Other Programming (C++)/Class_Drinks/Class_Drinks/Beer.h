#pragma once
#include "Alcoholic_Drinks.h"

enum class Raw_Mat // ���� ����� ��� ����
{
	Wheat, // �������
	Barley, // ������
	Ginger // ������
};

class Beer :
	public Alcoholic_Drinks // ��������� �� ������ "����������� �������"
{
private:
	Raw_Mat mater; // ��������, �� �������� ������� ����
public:
	Beer(string, int, double, Raw_Mat); // ����������� ��� ���� (��������, ����� � ��, ������� ������, ��������)
	virtual ~Beer(); // ����������� ����������
	string get_name() const; // ������ (���������� �������� ����)
	int get_volume() const; // ������ (���������� ����� ����)
	double get_alc_perc() const; // ������ (���������� ������� �������� � ����)
	Raw_Mat get_mater() const; // ������ ��� ���������, �� �������� ������� ���� (��� ������� � ����� ��� ������ �� ���������)
	void output_mater(ostream& out) const; // ��� ������ ���� ��������� � �����
};