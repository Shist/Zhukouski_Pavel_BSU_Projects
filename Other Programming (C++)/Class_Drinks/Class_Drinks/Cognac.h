#pragma once
#include "Alcoholic_Drinks.h"

enum class Excerpt
{ // ���� �������
	deLuxe,
	Superior,
	Vieux,
	GrandReserve
};

class Cognac :
	public Alcoholic_Drinks // ��������� �� ������ "����������� �������"
{
private:
	Excerpt exc;
public:
	Cognac(string, int, double, Excerpt); // ����������� ��� ������� (��������, ����� � ��, ������� ������, ���)
	virtual ~Cognac(); // ����������� ����������
	string get_name() const; // ������ (���������� �������� �������)
	int get_volume() const; // ������ (���������� ����� �������)
	double get_alc_perc() const; // ������ (���������� ������� �������� � �������)
	Excerpt get_exc() const; // ������ (���������� ��� �������)
};