#pragma once
class Fraction {
private:
	double value;
	long num;
	long den;
	void reduction(long, long);

public:
	Fraction();
	Fraction(long long, long long);
	void setNum(long long);
	void setDen(long long);

	long getNum();
	long getDen();
	void Print();
	void decimalPrint();

	Fraction operator* (const Fraction&);
	Fraction operator/ (const Fraction&);
	Fraction operator+ (const Fraction&);
	Fraction operator- (const Fraction&);
	Fraction operator- () const;

	bool operator== (const Fraction& p);
	bool operator!= (const Fraction& p);
	bool operator> (const Fraction& p);
	bool operator< (const Fraction& p);
	bool operator>= (const Fraction& p);
	bool operator<= (const Fraction& p);



};
