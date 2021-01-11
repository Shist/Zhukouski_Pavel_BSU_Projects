#include "Fraction.h"


void Fraction::reduction() // Функция для сокращения дробей (реализация)
{
	if (zn < 0)
	{
		zn = -zn;
		ch = -ch;
	}
	long temp = (abs(ch) > abs(zn)) ? zn : ch;
	temp = abs(temp);
	for (long i = temp; i > 1; i--)
	{
		if (ch%i == 0 && zn%i == 0)
		{
			ch /= i;
			zn /= i;
		}
	}
	if (ch == 0) zn = 1;
}

Fraction::Fraction() // Конструктор по умолчанию
{
	ch = 0;
	zn = 1;
}

Fraction::Fraction(long long ach, long long azn) // Конструктор для дробей (реализация)
{
	set_ch(ach);
	set_zn(azn);
	this->reduction();
}

Fraction::~Fraction() // Виртуальный деструктор
{
}

void Fraction::set_ch(long long ach) // Реализация set-метода для числителя
{
	if (ach > 2147483647) throw exception("Error! You are out of range for long values!"); // Проверка на переполнение
	ch = ach;
}

long Fraction::get_ch() const // Реализация get-метода для числителя
{
	return ch;
}

void Fraction::set_zn(long long azn) // Реализация set-метода для знаменателя
{
	if (azn > 2147483647) throw exception("Error! You are out of range for long values!"); // Проверка на переполнение
	if (azn == 0) throw exception("Error! An attempt was made to divide by zero!"); // Если знаменатель равен нулю, выбрасываем исключениe
	zn = azn;
}

long Fraction::get_zn() const // Реализация get-метода для знаменателя
{
	return zn;
}

Fraction Fraction::operator + (const Fraction & P) const // Реализация операции сложения
{
	Fraction X;
	X.set_ch(ch * P.get_zn() + zn * P.get_ch());
	X.set_zn(zn * P.get_zn());
	X.reduction();
	return X;
}

Fraction Fraction::operator - (const Fraction & P) const // Реализация операции вычитания
{
	Fraction X;
	X.set_ch(ch * P.get_zn() - zn * P.get_ch());
	X.set_zn(zn * P.get_zn());
	X.reduction();
	return X;
}

Fraction Fraction::operator - ()const // Реализация операции смены знака (унарный минус)
{
	Fraction X;
	X.set_ch(-ch);
	X.set_zn(zn);
	return(X);
}

Fraction Fraction::operator * (const Fraction & P) const // Реализация операции умножения
{
	Fraction X;
	X.set_ch(ch * P.get_ch());
	X.set_zn(zn * P.get_zn());
	X.reduction();
	return X;
}

Fraction Fraction::operator / (const Fraction & P) const // Реализация операции деления
{
	Fraction X;
	X.set_ch(ch * P.get_zn());
	X.set_zn(zn * P.get_ch());
	X.reduction();
	return X;
}

// Ниже реализованы все 6 операций сравнения...
bool Fraction::operator < (const Fraction&F) const
{
	if (ch*F.get_zn() < F.ch*get_zn()) return true;
	else return false;
}

bool Fraction::operator > (const Fraction&F) const
{
	if (ch*F.get_zn() > F.get_ch()*zn) return true;
	else return false;
}

bool Fraction::operator <= (const Fraction&F) const
{
	if (ch*F.get_zn() <= F.get_ch()*zn) return true;
	else return false;
}

bool Fraction::operator >= (const Fraction&F) const
{
	if (ch*F.get_zn() >= F.get_ch()*zn) return true;
	else return false;
}

bool Fraction::operator == (const Fraction&F) const
{
	if (ch*F.get_zn() == F.get_ch()*zn) return true;
	else return false;
}

bool Fraction::operator != (const Fraction&F) const
{
	if (ch*F.get_zn() != F.get_ch()*zn) return true;
	else return false;
}

double Fraction::SeeDouble() const // Реализация функции для вывода дроби в формате double
{
	return ((double)ch / zn);
}

ostream & operator << (ostream & s, const Fraction & a) // Реализация функции, нужной для вывода дроби
{
	if (a.get_ch() == 0)
	{
		s << 0;
		return s;
	}
	else
		s << a.get_ch();
	if (a.get_zn() != 1)
	{
		s << '/' << a.get_zn();
	}
	return s;
}