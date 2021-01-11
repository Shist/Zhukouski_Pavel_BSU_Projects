#pragma once
#include "Alcoholic_Drinks.h"

enum class Color // ���� ����
{
	White, // �����
	Red // �������
};

class Wine :
	public Alcoholic_Drinks // ��������� �� ������ "����������� �������"
{
private:
	Color colour; // ���� ����
public:
	Wine(string, int, double, Color); // ����������� ��� ���� (��������, ����� � ��, ������� ������, ����)
	virtual ~Wine(); // ����������� ����������
	string get_name() const; // ������ (���������� �������� ����)
	int get_volume() const; // ������ (���������� ����� ����)
	double get_alc_perc() const; // ������ (���������� ������� �������� � ����)
	Color get_colour() const; // ������ ��� ����� ���� (��� ������� � ����� ��� ������ �� ���������)
	void output_colour(ostream& out) const; // ��� ������ ���� ���� � �����
};