#include "WeightSystem.h"

WeightSystem::WeightSystem(long long new_pud, long long new_fut, long long new_zol)
{ // Конструктор
	Set_Pud(new_pud);
	Set_Fut(new_fut);
	Set_Zol(new_zol);
}

WeightSystem::WeightSystem()
{ // Конструктор по умолчанию (на всякий случай)
	pud = 0;
	fut = 0;
	zol = 0;
}

WeightSystem::~WeightSystem()
{
	// Виртуальный деструктор
}

int WeightSystem::Get_Pud() const
{ // Геттер для пудов
	return pud;
}

int WeightSystem::Get_Fut() const
{ // Геттер для фунтов
	return fut;
}

int WeightSystem::Get_Zol() const
{ // Геттер для золотников
	return zol;
}

void WeightSystem::Set_Pud(long long new_pud)
{ // Сеттер для пудов
	if (new_pud < 0) // Проверка на неотрицательность пудов
		throw exception("The value of poods cannot be negative!");
	if (new_pud > INT32_MAX) // Проверка на переполнение пудов
		throw exception("Too much poods! Overflow possible!");
	pud = (int)new_pud;
}

void WeightSystem::Set_Fut(long long new_fut)
{ // Сеттер для фунтов
	if (new_fut < 0) // Проверка на неотрицательность фунтов
		throw exception("The value of pounds cannot be negative!");
	if (new_fut > 39) // Проверка на максимальное возможное количество фунтов
		throw exception("The value of pounds is higher than the permissible!");
	fut = (int)new_fut;
}

void WeightSystem::Set_Zol(long long new_zol)
{ // Сеттер для золотников
	if (new_zol < 0) // Проверка на неотрицательность золотников
		throw exception("The value of spools cannot be negative!");
	if (new_zol > 95) // Проверка на максимальное возможное количество золотников
		throw exception("The value of the spools is higher than permissible!");
	zol = (int)new_zol;
}

bool WeightSystem::operator == (const WeightSystem &W) const
{ // Равенство
	return (pud == W.Get_Pud() && fut == W.Get_Fut() && zol == W.Get_Zol());
}

bool WeightSystem::operator != (const WeightSystem &W) const
{ // Неравенство
	return !(*this == W);
}

bool WeightSystem::operator < (const WeightSystem &W) const
{ // Меньше
	if (pud < W.Get_Pud()) return true;
	else if (pud > W.Get_Pud()) return false;
	else
	{
		if (fut < W.Get_Fut()) return true;
		else if (fut > W.Get_Fut()) return false;
		else
		{
			return (zol < W.Get_Zol());
		}
	}
}

bool WeightSystem::operator <= (const WeightSystem &W) const
{ // Меньше либо равно
	if (pud < W.Get_Pud()) return true;
	else if (pud > W.Get_Pud()) return false;
	else
	{
		if (fut < W.Get_Fut()) return true;
		else if (fut > W.Get_Fut()) return false;
		else
		{
			return (zol <= W.Get_Zol());
		}
	}
}

bool WeightSystem::operator > (const WeightSystem &W) const
{ // Больше
	return !(*this <= W);
}

bool WeightSystem::operator >= (const WeightSystem &W) const
{ // Больше либо равно
	return !(*this < W);
}

ostream & operator << (ostream &s, const WeightSystem &W)
{ // Функция для форматированного вывода значения веса
	bool check = true;
	if (W.Get_Pud() != 0)
	{
		s << W.Get_Pud() << " pud.,";
		check = false;
	}
	if (W.Get_Fut() != 0)
	{
		s << W.Get_Fut() << " fut.,";
		check = false;
	}
	if (W.Get_Zol() != 0)
	{
		s << W.Get_Zol() << " zol.,";
		check = false;
	}
	if (check)
		s << "0 zol.,";
	return s;
}

void WeightSystem::WeightReduction()
{ // Функция, упрощающая значение веса, если это возможно
	if (zol > 95)
	{
		fut += (zol / 96);
		zol %= 96;
	}
	else if (zol < 0)
	{
		int temp = (zol / -96) + 1;
		fut -= temp;
		zol += (temp * 96);
	}
	if (fut > 39)
	{
		pud += (fut / 40);
		fut %= 40;
	}
	else if (fut < 0)
	{
		int temp = (fut / -40) + 1;
		pud -= temp;
		fut += (temp * 40);
	}
	if (pud < 0)
		throw exception("The value of the whole weight cannot be negative!");
}

WeightSystem WeightSystem::operator + (const WeightSystem &W) const
{ // Сложение
	WeightSystem Result = WeightSystem();
	Result.pud = this->pud + W.Get_Pud();
	Result.fut = this->fut + W.Get_Fut();
	Result.zol = this->zol + W.Get_Zol();
	Result.WeightReduction();
	return Result;
}

WeightSystem WeightSystem::operator - (const WeightSystem &W) const
{ // Вычитание
	WeightSystem Result = WeightSystem();
	Result.pud = this->pud - W.Get_Pud();
	Result.fut = this->fut - W.Get_Fut();
	Result.zol = this->zol - W.Get_Zol();
	Result.WeightReduction();
	return Result;
}

WeightSystem& WeightSystem::operator += (const WeightSystem &W)
{ // Сложение с присвоением
	pud += W.Get_Pud();
	fut += W.Get_Fut();
	zol += W.Get_Zol();
	WeightReduction();
	return *this;
}

WeightSystem& WeightSystem::operator -= (const WeightSystem &W)
{ // Вычитание с присвоением
	pud -= W.Get_Pud();
	fut -= W.Get_Fut();
	zol -= W.Get_Zol();
	WeightReduction();
	return *this;
}

double WeightSystem::GetWeight()
{ // Получить информацию о весе объекта
	return kilo_in_zol * ((pud * 40 + fut) * 96 + zol);
}