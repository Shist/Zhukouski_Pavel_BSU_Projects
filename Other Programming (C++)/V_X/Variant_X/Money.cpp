#include "Money.h"
#include <iostream>
#include <exception>
#include <cmath>

using namespace std;

Money::Money()
{
	pd = 0;
	sh = 0;
	p = 0;
}

Money::Money(int _pd, int _sh, double _p)
{
	if (_pd >= 0)
	{
		pd = _pd;
	}
	else
	{
		throw exception("The number must be > 0");
	}

	if (_sh >= 0 && _sh <= 20)
	{
		sh = _sh;
	}
	else
	{
		throw exception("The number of sh. must be >= 0 but < 20");
	}

	if (_p >= 0 && _p <= 12)
	{
		p = _p;
	}
	else
	{
		throw exception("The number of p. must be >= 0 but < 12");
	}
}

ostream& operator << (ostream& s, const Money& k)
{
	s << k.pd << "pd. " << k.sh << "sh. " << k.p << "p. " << endl;
	return s;
}

Money Money::operator + (Money added) const
{
	Money result;
	result.pd = pd + added.pd;
	result.sh = sh + added.sh;
	result.p = p + added.p;

	while (result.p >= 12)
	{
		result.sh++;
		result.p -= 12;
	}

	while (result.sh >= 20)
	{
		result.pd++;
		result.sh -= 20;
	}

	if (result.pd > 1000000000)
	{
		cout << "You have too much money!" << endl;
	}

	return result;
}

Money Money::operator - (Money added) const
{
	Money result;
	result.pd = pd - added.pd;
	result.sh = sh - added.sh;
	result.p = p - added.p;

	while (result.p < 0)
	{
		result.sh -= 1;
		result.p += 12;
	}

	while (result.sh < 0)
	{
		result.pd -= 1;
		result.sh += 20;
	}

	if (result.pd < 0)
	{
		return -(added - *this);
	}

	return result;
}

Money Money::operator - () const
{
	Money result;
	result.pd = -pd;
	result.sh = sh;
	result.p = p;
	return result;
}

Money Money::operator += (const Money &added)
{
	pd += added.pd;
	sh += added.sh;
	p += added.p;

	if (p >= 12)
	{
		sh++;
		p -= 12;
	}

	if (sh >= 20)
	{
		pd++;
		sh -= 20;
	}

	if (pd > 1000000000)
	{
		cout << "You have too much money!" << endl;
	}

	return *this;
}
Money Money::operator -= (const Money &added)
{
	pd -= added.pd;
	sh -= added.sh;
	p -= added.p;

	if (p < 0)
	{
		sh--;
		p += 12;
	}

	if (sh < 0)
	{
		pd--;
		sh += 20;
	}

	if (pd < 0)
	{
		return -(added - *this);
	}

	return *this;
}

bool Money::operator < (Money &added) const
{
	if (pd < added.pd)
	{
		return true;
	}
	else
	{
		if (pd == added.pd && sh > added.sh)
		{
			return false;
		}
		else
		{
			if (sh == added.sh && pd < added.pd)
			{
				return true;
			}
			else
			{
				if (pd == added.pd && sh == added.sh && p > added.p)
				{
					return false;
				}
				else
				{
					if (pd == added.pd && sh == added.sh && p < added.p)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
}

bool Money::operator > (Money &added) const
{
	if (pd > added.pd)
	{
		return true;
	}
	else
	{
		if (pd == added.pd && sh < added.sh)
		{
			return false;
		}
		else
		{
			if (sh == added.sh && p > added.p)
			{
				return true;
			}
			else
			{
				if (pd == added.pd && sh == added.sh && p > added.p)
				{
					return true;
				}
				else
				{
					if (pd == added.pd && sh == added.sh && p < added.p)
					{
						return false;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
}

bool Money::operator <= (Money &added) const
{
	if (pd <= added.pd)
	{
		return true;
	}
	else
	{
		if (pd == added.pd && sh > added.sh)
		{
			return false;
		}
		else
		{
			if (sh == added.sh && p <= added.p)
			{
				return true;
			}
			else
			{
				if (pd == added.pd && sh == added.sh && p >= added.p)
				{
					return false;
				}
				else
				{
					if (pd == added.pd && sh == added.sh && p <= added.p)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
}

bool Money::operator >= (Money &added) const
{
	if (pd >= added.pd)
	{
		return true;
	}
	else
	{
		if (pd == added.pd && sh < added.sh)
		{
			return false;
		}
		else
		{
			if (sh == added.sh && p >= added.p)
			{
				return true;
			}
			else
			{
				if (pd == added.pd && sh == added.sh && p >= added.p)
				{
					return true;
				}
				else
				{
					if (pd == added.pd && sh == added.sh && p <= added.p)
					{
						return false;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
}

bool Money::operator == (Money &added) const
{
	if (pd == added.pd && sh == added.sh && p == added.p)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Money::operator != (Money &added) const
{
	if (pd != added.pd || sh != added.sh || p != added.p)
	{
		return true;
	}
	else
	{
		if (pd == added.pd || sh == added.sh || p == added.p)
		{
			return false;
		}
		else
		{
			return false;
		}
	}
}

void Money::Precision()
{
	double n = 2 * p;
	n = n - floor(n);

	if (n != 0)
	{
		if (p - floor(p) < 0.5)
		{
			p = floor(p);
		}
		else
		{
			p = p - floor(p) + 0.5;
		}
	}
}

Money::~Money()
{
}
