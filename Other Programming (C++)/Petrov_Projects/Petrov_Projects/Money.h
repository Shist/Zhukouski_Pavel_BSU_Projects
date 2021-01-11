#pragma once

class Money {
private:
	bool debt;
	double pennyValue;
	long long pound;
	long long shilling;
	double penny;
	Money(double pennyValue);
	void setPennyValue(double);

public:
	Money();
	Money(long long pound, long long shilling, double penny);

	friend bool operator== (const Money& p, const Money& p1);
	friend bool operator!= (const Money& p, const Money& p1);
	friend bool operator> (const Money& p, const Money& p1);
	friend bool operator< (const Money& p, const Money& p1);
	friend bool operator>= (const Money& p, const Money& p1);
	friend bool operator<= (const Money& p, const Money& p1);

	void Print();
	double ConverToPenny(long long pound, long long shilling, double penny);
	void PennyConvert(double& pennyValue);

	Money operator - () const;
	Money operator + (const Money& p) const;
	Money operator - (const Money& p) const;
	Money& operator += (const Money& p);
	Money& operator -= (const Money& p);
};

bool operator== (const Money& p, const Money& p1);
bool operator!= (const Money& p, const Money& p1);
bool operator> (const Money& p, const Money& p1);
bool operator< (const Money& p, const Money& p1);
bool operator>= (const Money& p, const Money& p1);
bool operator<= (const Money& p, const Money& p1);