#pragma once
#include <iostream>
#include <exception>
using namespace std;

class WeightSystem
{
private:
	const double kilo_in_zol = 0.004265625; // ���������� ��������� � ����� ���������
	int pud; // ����
	int fut; // �����
	int zol; // ���������
	WeightSystem(); // ����������� �� ��������� (�� ������ ������ ����� �����)
	void WeightReduction(); // �������, ������� ����� �������� �������� ����, ���� ��� ��������
public:
	WeightSystem(long long, long long, long long); // �����������
	virtual ~WeightSystem(); // ����������� ����������
	int Get_Pud() const; // ������ ��� �����
	int Get_Fut() const; // ������ ��� ������
    int Get_Zol() const; // ������ ��� ����������
	void Set_Pud(long long); // ������ ��� �����
	void Set_Fut(long long); // ������ ��� ������
	void Set_Zol(long long); // ������ ��� ����������
	bool operator == (const WeightSystem&) const; // ���������
	bool operator != (const WeightSystem&) const; // �����������
	bool operator < (const WeightSystem&) const; // ������
	bool operator <= (const WeightSystem&) const; // ������ ���� �����
	bool operator > (const WeightSystem&) const; // ������
	bool operator >= (const WeightSystem&) const; // ������ ���� �����
	friend ostream& operator << (ostream&, const WeightSystem&); // ������� ��� ���������������� ������ �������� ����
	WeightSystem operator + (const WeightSystem&) const; // ��������
	WeightSystem operator - (const WeightSystem&) const; // ���������
	WeightSystem& operator += (const WeightSystem&); // �������� � �����������
	WeightSystem& operator -= (const WeightSystem&); // ��������� � �����������
	double GetWeight(); // �������� ���������� � ���� �������
};