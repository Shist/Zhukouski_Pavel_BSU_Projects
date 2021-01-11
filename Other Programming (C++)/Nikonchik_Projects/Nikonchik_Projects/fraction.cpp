#include "fraction.h"
#include <iostream>
#include <cmath>
#include "fraction_exception.h"
#include <algorithm>

using namespace std;

void fraction::PrintFraction()
{
	cout << (this->num * 1.0) / (this->den * 1.0) << endl;
}

void fraction::WholeFraction()
{
	cout << this->num << "/";
	cout << this->den << endl;
}

long fraction::Getnum() const
{
	return num;
}

long fraction::Getden() const
{
	return den;
}

void fraction::Setnum(long long anum)
{
	if (anum > INT32_MAX)
		throw exception("Значение числителя слишком большое! Максимально возможное: 2147483647");
	num = anum;
	reduction();
}

void fraction::Setden(long long aden)
{
	if (aden > INT32_MAX)
		throw exception("Значение знаменателя слишком большое! Максимально возможное: 2147483647");
	if (aden == 0)
		throw exception("Знаминатель не может быть равным нулю");
	den = aden;
	reduction();
}

void fraction::reduction()
{

	int nod = abs(gcd(num, den));
	num /= nod;
	den /= nod;
	if (den < 0)
	{
		den = -den;
		num = -num;
	}
}

long fraction::gcd(long a, long b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

fraction::fraction()
{
	this->num = 0;
	this->den = 1;
}

fraction::fraction(long long anum, long long aden)
{
	Setnum(anum);
	Setden(aden);
}

fraction fraction::operator + (const fraction& p) const
{
	fraction x;
	x.Setnum((long long)num * (long long)p.Getden() + (long long)p.Getnum() * (long long)den);
	x.Setden((long long)den * (long long)p.Getden());
	x.reduction();
	return x;
}

fraction fraction::operator - (const fraction& p) const // Реализация операции вычитания
{
	fraction x;
	x.Setnum((long long)num * (long long)p.Getden() - (long long)den * (long long)p.Getnum());
	x.Setden((long long)den * (long long)p.Getden());
	x.reduction();
	return x;
}

fraction fraction::operator - ()const // Реализация операции смены знака (унарный минус)
{
	fraction x;
	x.Setnum(-num);
	x.Setden(den);
	return(x);
}

fraction fraction::operator * (const fraction& p) const // Реализация операции умножения
{
	fraction x;
	x.Setnum((long long)num * (long long)p.Getnum());
	x.Setden((long long)den * (long long)p.Getden());
	x.reduction();
	return x;
}

fraction fraction::operator / (const fraction& p) const // Реализация операции деления
{
	fraction x;
	x.Setnum((long long)num * (long long)p.Getden());
	x.Setden((long long)den * (long long)p.Getnum());
	x.reduction();
	return x;
}

bool fraction::operator==(const fraction& p) const
{

	return (num == p.Getnum() && den == p.Getden());
}

bool fraction::operator!=(const fraction& p) const
{
	return (!this -> operator==(p));
}

bool fraction::operator<(const fraction& p) const
{
	fraction x((long long)num * (long long)p.Getden() - (long long)p.Getnum() * (long long)den, (long long)den * (long long)p.Getden());
	if (x.num < 0)
		return true;
	else
		return false;
}

bool fraction::operator<=(const fraction& p) const
{
	fraction x((long long)num * (long long)p.Getden() - (long long)p.Getnum() * (long long)den, (long long)den * (long long)p.Getden());
	if (x.num <= 0)
		return true;
	else
		return false;
}

bool fraction::operator>(const fraction& p) const
{
	return (!this -> operator<(p));
}

bool fraction::operator>=(const fraction& p) const
{
	return (!this -> operator<=(p));
}

ostream& operator<<(ostream& d, const fraction& p)
{
	d << p.Getnum() / p.Getden();
	return d;
}