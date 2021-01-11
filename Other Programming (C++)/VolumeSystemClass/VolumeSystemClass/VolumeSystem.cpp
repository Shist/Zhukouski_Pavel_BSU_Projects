#include "VolumeSystem.h"

VolumeSystem::VolumeSystem(long long new_shtof, long long new_bottl, long double new_chrk)
{ // Конструктор
	Set_Shtof(new_shtof);
	Set_Bottl(new_bottl);
	Set_Chrk(new_chrk);
}

VolumeSystem::VolumeSystem()
{ // Конструктор по умолчанию (на всякий случай)
	shtof = 0;
	bottl = 0;
	chrk = 0.0;
}

VolumeSystem::~VolumeSystem()
{
	// Виртуальный деструктор
}

int VolumeSystem::Get_Shtof() const
{ // Геттер для штоф
	return shtof;
}

int VolumeSystem::Get_Bottl() const
{ // Геттер для бутылок
	return bottl;
}

double VolumeSystem::Get_Chrk() const
{ // Геттер для чарок
	return chrk;
}

void VolumeSystem::Set_Shtof(long long new_shtof)
{ // Сеттер для штоф
	if (new_shtof < 0) // Проверка на неотрицательность штоф
		throw exception("The value of damns cannot be negative!");
	if (new_shtof > INT32_MAX) // Проверка на переполнение штоф
		throw exception("Too much damns! Overflow possible!");
	shtof = (int)new_shtof;
}

void VolumeSystem::Set_Bottl(long long new_bottl)
{ // Сеттер для бутылок
	if (new_bottl < 0) // Проверка на неотрицательность бутылок
		throw exception("The value of bottles cannot be negative!");
	if (new_bottl > 1) // Проверка на максимальное возможное количество бутылок
		throw exception("The value of bottles is higher than the permissible!");
	bottl = (int)new_bottl;
}

void VolumeSystem::Set_Chrk(long double new_chrk)
{ // Сеттер для чарок
	if (new_chrk < 0.0) // Проверка на неотрицательность чарок
		throw exception("The value of charms cannot be negative!");
	if (new_chrk > 4.75) // Проверка на максимальное возможное количество чарок
		throw exception("The value of the charms is higher than permissible!");
	long long temp = (long long)(new_chrk * 100);
	if (temp % 25 != 0)
		throw exception("The value of the charms must be set with an accuracy of 1/4!");
	chrk = (double)new_chrk;
}

bool VolumeSystem::operator == (const VolumeSystem &V) const
{ // Равенство
	return (shtof == V.Get_Shtof() && bottl == V.Get_Bottl() && chrk == V.Get_Chrk());
}

bool VolumeSystem::operator != (const VolumeSystem &V) const
{ // Неравенство
	return !(*this == V);
}

bool VolumeSystem::operator < (const VolumeSystem &V) const
{ // Меньше
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
{ // Меньше либо равно
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
{ // Больше
	return !(*this <= V);
}

bool VolumeSystem::operator >= (const VolumeSystem &V) const
{ // Больше либо равно
	return !(*this < V);
}

ostream & operator << (ostream &s, const VolumeSystem &V)
{ // Функция для форматированного вывода значения объёма
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
{ // Функция, упрощающая значение объёма, если это возможно
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
{ // Сложение
	VolumeSystem Result = VolumeSystem();
	Result.shtof = this->shtof + V.Get_Shtof();
	Result.bottl = this->bottl + V.Get_Bottl();
	Result.chrk = this->chrk + V.Get_Chrk();
	Result.VolumeReduction();
	return Result;
}

VolumeSystem VolumeSystem::operator - (const VolumeSystem &V) const
{ // Вычитание
	VolumeSystem Result = VolumeSystem();
	Result.shtof = this->shtof - V.Get_Shtof();
	Result.bottl = this->bottl - V.Get_Bottl();
	Result.chrk = this->chrk - V.Get_Chrk();
	Result.VolumeReduction();
	return Result;
}

VolumeSystem& VolumeSystem::operator += (const VolumeSystem &V)
{ // Сложение с присвоением
	shtof += V.Get_Shtof();
	bottl += V.Get_Bottl();
	chrk += V.Get_Chrk();
	VolumeReduction();
	return *this;
}

VolumeSystem& VolumeSystem::operator -= (const VolumeSystem &V)
{ // Вычитание с присвоением
	shtof -= V.Get_Shtof();
	bottl -= V.Get_Bottl();
	chrk -= V.Get_Chrk();
	VolumeReduction();
	return *this;
}

double VolumeSystem::GetVolume()
{ // Получить информацию о весе объекта
	return liters_in_chrk * ((shtof * 2 + bottl) * 5 + chrk);
}