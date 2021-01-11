#include "Fraction.h"


void Fraction::reduction() // ������� ��� ���������� ������ (����������)
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

Fraction::Fraction() // ����������� �� ���������
{
	ch = 0;
	zn = 1;
}

Fraction::Fraction(long long ach, long long azn) // ����������� ��� ������ (����������)
{
	set_ch(ach);
	set_zn(azn);
	this->reduction();
}

Fraction::~Fraction() // ����������� ����������
{
}

void Fraction::set_ch(long long ach) // ���������� set-������ ��� ���������
{
	if (ach > 2147483647) throw exception("Error! You are out of range for long values!"); // �������� �� ������������
	ch = ach;
}

long Fraction::get_ch() const // ���������� get-������ ��� ���������
{
	return ch;
}

void Fraction::set_zn(long long azn) // ���������� set-������ ��� �����������
{
	if (azn > 2147483647) throw exception("Error! You are out of range for long values!"); // �������� �� ������������
	if (azn == 0) throw exception("Error! An attempt was made to divide by zero!"); // ���� ����������� ����� ����, ����������� ���������e
	zn = azn;
}

long Fraction::get_zn() const // ���������� get-������ ��� �����������
{
	return zn;
}

Fraction Fraction::operator + (const Fraction & P) const // ���������� �������� ��������
{
	Fraction X;
	X.set_ch(ch * P.get_zn() + zn * P.get_ch());
	X.set_zn(zn * P.get_zn());
	X.reduction();
	return X;
}

Fraction Fraction::operator - (const Fraction & P) const // ���������� �������� ���������
{
	Fraction X;
	X.set_ch(ch * P.get_zn() - zn * P.get_ch());
	X.set_zn(zn * P.get_zn());
	X.reduction();
	return X;
}

Fraction Fraction::operator - ()const // ���������� �������� ����� ����� (������� �����)
{
	Fraction X;
	X.set_ch(-ch);
	X.set_zn(zn);
	return(X);
}

Fraction Fraction::operator * (const Fraction & P) const // ���������� �������� ���������
{
	Fraction X;
	X.set_ch(ch * P.get_ch());
	X.set_zn(zn * P.get_zn());
	X.reduction();
	return X;
}

Fraction Fraction::operator / (const Fraction & P) const // ���������� �������� �������
{
	Fraction X;
	X.set_ch(ch * P.get_zn());
	X.set_zn(zn * P.get_ch());
	X.reduction();
	return X;
}

// ���� ����������� ��� 6 �������� ���������...
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

double Fraction::SeeDouble() const // ���������� ������� ��� ������ ����� � ������� double
{
	return ((double)ch / zn);
}

ostream & operator << (ostream & s, const Fraction & a) // ���������� �������, ������ ��� ������ �����
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