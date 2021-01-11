#pragma once
#include <iostream>

using namespace std;

class fraction
{
private:
	long num;
	long den;
	static long gcd(long a, long b);
	void reduction();

public:
	void PrintFraction();//для вывода в double
	void WholeFraction();//для дробей
	long Getnum() const;
	long Getden() const;
	void Setnum(long long anum);
	void Setden(long long aden);

	fraction();
	fraction(long long num, long long den);

	fraction operator+(const fraction&) const;
	fraction operator-(const fraction&) const;
	fraction operator*(const fraction&) const;
	fraction operator/(const fraction&) const;
	fraction operator-() const;

	bool operator==(const fraction& a) const;
	bool operator!=(const fraction& a) const;
	bool operator< (const fraction& a) const;
	bool operator<=(const fraction& a) const;
	bool operator> (const fraction& a) const;
	bool operator>=(const fraction& a) const;

	friend ostream& operator <<(ostream&, const fraction&);
};
