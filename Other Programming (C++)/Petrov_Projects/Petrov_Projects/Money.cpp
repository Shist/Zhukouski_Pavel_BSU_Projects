#include "Money.h"
#include <iostream>
#include <cmath>
using namespace std;


Money::Money() {
	setPennyValue(0);
	pound = 0;
	shilling = 0;
	penny = 0;
	debt = false;
}

Money::Money(long long pound, long long shilling, double penny) {
	double tmp = penny * 2;
	if (pound > 1000000000 || shilling >= 20 || penny >= 12 || pound < 0 || shilling < 0 || penny < 0 || tmp != (int(tmp))) {
		throw exception("¬ведено некорректное значение денежных средств!");
	}
	setPennyValue(ConverToPenny(pound, shilling, penny));
}

void Money::setPennyValue(double aPennyValue) {
	pennyValue = aPennyValue;
	if (abs(pennyValue) > 240000000000.0) {
		throw exception("—умма перешла планку в миллион пенсов!");
	}
}

void Money::Print() {
	PennyConvert(pennyValue);
	if (pound == 0 && shilling != 0) {
		if (debt) {
			cout << "-";
		}
		cout << shilling << "sh." << penny << "p.";
	}
	else if (pound == 0 && shilling == 0) {
		if (debt) {
			cout << "-";
		}
		cout << penny << "p.";
	}
	else {
		if (debt) {
			cout << "-";
		}
		cout << pound << "pd." << shilling << "sh." << penny << "p.";
	}
}

double Money::ConverToPenny(long long pound, long long shilling, double penny) {
	return this->pennyValue = pound * 240 + shilling * 12 + penny;
}

void Money::PennyConvert(double& pennyValue) {
	if (pennyValue < 0) {
		this->debt = true;
		pennyValue = pennyValue * (-1);
	}
	else if (pennyValue >= 0) {
		this->debt = false;
	}
	this->pound = static_cast<long long>(floor(abs(pennyValue / 240)));
	this->shilling = static_cast <long long> (floor(abs(fmodf(pennyValue, 240) / 12)));
	this->penny = (pennyValue - (pound * 240 + shilling * 12));
	penny = 0.5 * floor(2.0 * abs(penny)) + 0.5 * floor(4 * fmod(abs(penny), 0.5));
}

Money  Money::operator - () const { // унарный минус
	Money X(0, 0, 0.0);
	X.setPennyValue((-1) * pennyValue);
	return X;
}
Money  Money::operator + (const Money& p) const {
	Money X(0, 0, 0.0);
	X.setPennyValue(pennyValue + pennyValue);
	return X;
}
Money  Money::operator - (const Money& p) const {
	Money X(0, 0, 0.0);
	X.setPennyValue(pennyValue - pennyValue);
	return X;
}
Money &Money::operator+= (const Money& p) {
	Money money(*this);
	pennyValue += p.pennyValue;
	setPennyValue(pennyValue);
	return money;
}
Money &Money::operator-= (const Money& p) {
	Money money(*this);
	pennyValue -= p.pennyValue;
	setPennyValue(pennyValue);
	return money;
}

bool operator== (const Money& p, const Money& p1) {
	return (p.pennyValue == p1.pennyValue);
}

bool operator!= (const Money& p, const Money& p1) {
	return !(p.pennyValue == p1.pennyValue);
}
bool operator> (const Money& p, const Money& p1) {
	return (p.pennyValue > p1.pennyValue);
}
bool operator< (const Money& p, const Money& p1) {
	return (p.pennyValue < p1.pennyValue);
}
bool operator>= (const Money& p, const Money& p1) {
	return (p.pennyValue >= p1.pennyValue);
}
bool operator<= (const Money& p, const Money& p1) {
	return (p.pennyValue <= p1.pennyValue);
}