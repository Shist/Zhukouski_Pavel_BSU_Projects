#pragma once
#include "Bottled_Drinks.h"

class Alcoholic_Drinks :
	public Bottled_Drinks // ��������� �� ������ "�������������� �������"
{
protected:
	double alc_perc; // ����, ��������� ���������� � ���������� ������ � ������� (� ���������)
public:
	Alcoholic_Drinks(); // ����������� (��������)
	virtual ~Alcoholic_Drinks(); // ����������� ����������
	virtual double get_alc_perc() const = 0; // ����������� ������ (������� ��������)
};