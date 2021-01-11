#include "Fraction.h"
#include <iostream>
#include <cmath>
using namespace std;

Fraction::Fraction() {
	setNum(0);
	setDen(1);
}

Fraction::Fraction(long long num, long long den) {
	setNum(num);
	setDen(den);
	reduction(num, den);
}

void Fraction::setNum(long long aNum) {
	if (aNum > INT32_MAX || aNum < INT32_MIN) {
		throw exception("Введено некорректное значение числителя, либо его переполнение!");
	}
	num = aNum;
}

void Fraction::setDen(long long aDen) {
	if (aDen > INT32_MAX || aDen < INT32_MIN) {
		throw exception("Введено некорректное значение знаменателя, либо его переполнение!");
	}
	if (aDen == 0) {
		throw exception("Знаменатель не может быть равен нулю!");
	}
	den = aDen;
}

long Fraction::getNum() {
	reduction(num, den);
	return num;
}

long Fraction::getDen() {
	reduction(num, den);
	return den;
}

void Fraction::Print() {
	reduction(num, den);
	if (num == 0) {
		cout << 0;
	}
	else if (abs(num) == abs(den)) {
		cout << getNum();
	}
	else {
		cout << getNum() << "/" << getDen();
	}
}

void Fraction::decimalPrint() {
	reduction(num, den);
	if (num == 0) {
		cout << 0;
	}
	else if (abs(num) == abs(den)) {
		cout << getNum();
	}
	else {
		cout << (this->num * 1.0) / (this->den*1.0);
	}
}

void Fraction::reduction(long num, long den) {
	long a = abs(num);
	long b = abs(den);

	while (a != 0 && b != 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	long nod = a + b;
	this->num = num / nod;
	this->den = den / nod;
}

Fraction Fraction::operator* (const Fraction& p) {
	return Fraction(num * p.num, den * p.den);
}
Fraction Fraction::operator/ (const Fraction& p) {
	return Fraction(num * p.den, den * p.num);
}
Fraction Fraction::operator+ (const Fraction& p) {
	return Fraction(num * p.den + p.num * den, den * p.den);
}
Fraction Fraction::operator- (const Fraction& p) {
	return Fraction(num * p.den - p.num * den, den * p.den);
}
Fraction Fraction::operator - () const {
	return Fraction(-num, den);
}
bool Fraction::operator== (const Fraction& p) {
	return (num == p.num &&  den == p.den);
}
bool Fraction::operator!= (const Fraction& p) {
	return !(num == p.num && den == p.den);
}
bool Fraction::operator> (const Fraction& p) {
	return (num * p.den > p.num * den);
}
bool Fraction::operator< (const Fraction& p) {
	return (num * p.den < p.num* den);
}
bool Fraction::operator>= (const Fraction& p) {
	return (num * p.den >= p.num* den);
}
bool Fraction::operator<= (const Fraction& p) {
	return (num * p.den <= p.num * den);
}