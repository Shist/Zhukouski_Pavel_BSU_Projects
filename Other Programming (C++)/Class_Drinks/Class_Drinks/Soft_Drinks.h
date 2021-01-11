#pragma once
#include "Bottled_Drinks.h"

class Soft_Drinks :
	public Bottled_Drinks // ��������� �� ������ "�������������� �������"
{
protected:
	int exp_date; // ����, �������� ���������� � ����� �������� ������� � ���� ����� ��� ������������
public:
	Soft_Drinks(); // ����������� (��������)
	virtual ~Soft_Drinks(); // ����������� ����������
	virtual int get_exp_date() const = 0; // ����������� ������ (���� ��������)
	virtual void set_exp_date(int) = 0; // ����������� ������ ��� ��������� ���������� � ���������� ����� �������� ���� ��� ����� �������
};