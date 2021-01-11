#pragma once
#include <iostream>
#include <exception>
using namespace std;

class VolumeSystem
{
private:
	const double liters_in_chrk = 0.123; // ���������� ������ � ����� �����
	int shtof; // �����
	int bottl; // �������
	double chrk; // �����
	VolumeSystem(); // ����������� �� ��������� (�� ������ ������ ����� �����)
	void VolumeReduction(); // �������, ������� ����� �������� �������� ������, ���� ��� ��������
public:
	VolumeSystem(long long, long long, long double); // �����������
	virtual ~VolumeSystem(); // ����������� ����������
	int Get_Shtof() const; // ������ ��� ����
	int Get_Bottl() const; // ������ ��� �������
	double Get_Chrk() const; // ������ ��� �����
	void Set_Shtof(long long); // ������ ��� ����
	void Set_Bottl(long long); // ������ ��� �������
	void Set_Chrk(long double); // ������ ��� �����
	bool operator == (const VolumeSystem&) const; // ���������
	bool operator != (const VolumeSystem&) const; // �����������
	bool operator < (const VolumeSystem&) const; // ������
	bool operator <= (const VolumeSystem&) const; // ������ ���� �����
	bool operator > (const VolumeSystem&) const; // ������
	bool operator >= (const VolumeSystem&) const; // ������ ���� �����
	friend ostream& operator << (ostream&, const VolumeSystem&); // ������� ��� ���������������� ������ �������� ������
	VolumeSystem operator + (const VolumeSystem&) const; // ��������
	VolumeSystem operator - (const VolumeSystem&) const; // ���������
	VolumeSystem& operator += (const VolumeSystem&); // �������� � �����������
	VolumeSystem& operator -= (const VolumeSystem&); // ��������� � �����������
	double GetVolume(); // �������� ���������� �� ������ �������
};