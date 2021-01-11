#include "VolumeSystem.h"

VolumeSystem::VolumeSystem(long long new_shtof, long long new_bottl, long double new_chrk)
{ // �����������
	Set_Shtof(new_shtof);
	Set_Bottl(new_bottl);
	Set_Chrk(new_chrk);
}

VolumeSystem::VolumeSystem()
{ // ����������� �� ��������� (�� ������ ������)
	shtof = 0;
	bottl = 0;
	chrk = 0.0;
}

VolumeSystem::~VolumeSystem()
{
	// ����������� ����������
}

int VolumeSystem::Get_Shtof() const
{ // ������ ��� ����
	return shtof;
}

int VolumeSystem::Get_Bottl() const
{ // ������ ��� �������
	return bottl;
}

double VolumeSystem::Get_Chrk() const
{ // ������ ��� �����
	return chrk;
}

void VolumeSystem::Set_Shtof(long long new_shtof)
{ // ������ ��� ����
	if (new_shtof < 0) // �������� �� ����������������� ����
		throw exception("The value of damns cannot be negative!");
	if (new_shtof > INT32_MAX) // �������� �� ������������ ����
		throw exception("Too much damns! Overflow possible!");
	shtof = (int)new_shtof;
}

void VolumeSystem::Set_Bottl(long long new_bottl)
{ // ������ ��� �������
	if (new_bottl < 0) // �������� �� ����������������� �������
		throw exception("The value of bottles cannot be negative!");
	if (new_bottl > 1) // �������� �� ������������ ��������� ���������� �������
		throw exception("The value of bottles is higher than the permissible!");
	bottl = (int)new_bottl;
}

void VolumeSystem::Set_Chrk(long double new_chrk)
{ // ������ ��� �����
	if (new_chrk < 0.0) // �������� �� ����������������� �����
		throw exception("The value of charms cannot be negative!");
	if (new_chrk > 4.75) // �������� �� ������������ ��������� ���������� �����
		throw exception("The value of the charms is higher than permissible!");
	long long temp = (long long)(new_chrk * 100);
	if (temp % 25 != 0)
		throw exception("The value of the charms must be set with an accuracy of 1/4!");
	chrk = (double)new_chrk;
}

bool VolumeSystem::operator == (const VolumeSystem &V) const
{ // ���������
	return (shtof == V.Get_Shtof() && bottl == V.Get_Bottl() && chrk == V.Get_Chrk());
}

bool VolumeSystem::operator != (const VolumeSystem &V) const
{ // �����������
	return !(*this == V);
}

bool VolumeSystem::operator < (const VolumeSystem &V) const
{ // ������
	if (shtof < V.Get_Shtof()) return true;
	else if (shtof > V.Get_Shtof()) return false;
	else
	{
		if (bottl < V.Get_Bottl()) return true;
		else if (bottl > V.Get_Bottl()) return false;
		else
		{
			return (chrk < V.Get_Chrk());
		}
	}
}

bool VolumeSystem::operator <= (const VolumeSystem &V) const
{ // ������ ���� �����
	if (shtof < V.Get_Shtof()) return true;
	else if (shtof > V.Get_Shtof()) return false;
	else
	{
		if (bottl < V.Get_Bottl()) return true;
		else if (bottl > V.Get_Bottl()) return false;
		else
		{
			return (chrk <= V.Get_Chrk());
		}
	}
}

bool VolumeSystem::operator > (const VolumeSystem &V) const
{ // ������
	return !(*this <= V);
}

bool VolumeSystem::operator >= (const VolumeSystem &V) const
{ // ������ ���� �����
	return !(*this < V);
}

ostream & operator << (ostream &s, const VolumeSystem &V)
{ // ������� ��� ���������������� ������ �������� ������
	bool check = true;
	if (V.Get_Shtof() != 0)
	{
		s << V.Get_Shtof() << " sht.,";
		check = false;
	}
	if (V.Get_Bottl() != 0)
	{
		s << V.Get_Bottl() << " bot.,";
		check = false;
	}
	if (V.Get_Chrk() != 0)
	{
		s << V.Get_Chrk() << " chrk.,";
		check = false;
	}
	if (check)
		s << "0 chrk.,";
	return s;
}

void VolumeSystem::VolumeReduction()
{ // �������, ���������� �������� ������, ���� ��� ��������
	if (chrk > 4.75)
	{
		int temp = (int)(chrk / 5.0);
		bottl += temp;
		chrk -= (double)(temp * 5.0);
	}
	else if (chrk < 0.0)
	{
		int temp = (int)(chrk / -5.0) + 1;
		bottl -= temp;
		chrk += (double)(temp * 5.0);
	}
	if (bottl > 1)
	{
		shtof += (bottl / 2);
		bottl %= 2;
	}
	else if (bottl < 0)
	{
		int temp = (bottl / -2) + 1;
		shtof -= temp;
		bottl += (temp * 2);
	}
	if (shtof < 0)
		throw exception("The value of the whole volume cannot be negative!");
}

VolumeSystem VolumeSystem::operator + (const VolumeSystem &V) const
{ // ��������
	VolumeSystem Result = VolumeSystem();
	Result.shtof = this->shtof + V.Get_Shtof();
	Result.bottl = this->bottl + V.Get_Bottl();
	Result.chrk = this->chrk + V.Get_Chrk();
	Result.VolumeReduction();
	return Result;
}

VolumeSystem VolumeSystem::operator - (const VolumeSystem &V) const
{ // ���������
	VolumeSystem Result = VolumeSystem();
	Result.shtof = this->shtof - V.Get_Shtof();
	Result.bottl = this->bottl - V.Get_Bottl();
	Result.chrk = this->chrk - V.Get_Chrk();
	Result.VolumeReduction();
	return Result;
}

VolumeSystem& VolumeSystem::operator += (const VolumeSystem &V)
{ // �������� � �����������
	shtof += V.Get_Shtof();
	bottl += V.Get_Bottl();
	chrk += V.Get_Chrk();
	VolumeReduction();
	return *this;
}

VolumeSystem& VolumeSystem::operator -= (const VolumeSystem &V)
{ // ��������� � �����������
	shtof -= V.Get_Shtof();
	bottl -= V.Get_Bottl();
	chrk -= V.Get_Chrk();
	VolumeReduction();
	return *this;
}

double VolumeSystem::GetVolume()
{ // �������� ���������� � ���� �������
	return liters_in_chrk * ((shtof * 2 + bottl) * 5 + chrk);
}