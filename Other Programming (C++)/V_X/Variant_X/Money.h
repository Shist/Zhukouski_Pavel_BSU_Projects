#pragma once
#include <iostream>
#include <exception>

using namespace std;

class Money
{
private:
	int pd, sh;
	double p;
public:
	Money();
	Money(int _pd, int _sh, double _p);
	Money operator + (Money added) const;
	Money operator - (Money added) const;
	Money operator - () const;
	Money operator += (const Money& added);
	Money operator -= (const Money& added);

	bool operator < (Money& added) const;
	bool operator > (Money& added) const;
	bool operator <= (Money& added) const;
	bool operator >= (Money& added) const;
	bool operator == (Money& added) const;
	bool operator != (Money& added) const;

	friend ostream& operator <<(ostream&, const Money&);

	void Precision();
	virtual ~Money();
};

