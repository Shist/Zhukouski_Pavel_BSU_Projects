#pragma once // Предотвращаем ошибки, связанные с повторным описанием класса
#include <iostream>
#include <exception>
using namespace std;

class Fraction
{
private: // В приватной области введем две нужные нам переменные, чтобы потом с ними работать...
	long ch;
	long zn;
	void reduction(); // Функция, которая будет сокращать наши дроби
public:
	Fraction(); // Конструктор по умолчанию
	Fraction(long long, long long); // Конструктор для наших дробей
	virtual ~Fraction(); // Виртуальный деструктор

	long get_ch() const; // Для получения информации о числителе
	void set_ch(long long); // Для изменения информации о числителе

	long get_zn() const; // Для получения информации о знаменателе
	void set_zn(long long); // Для изменения информации о знаменателе

	Fraction operator + (const Fraction&) const; // Сложение
	Fraction operator - (const Fraction&) const; // Вычитание
	Fraction operator - () const; // Изменение знака (унарный минус)
	Fraction operator * (const Fraction &) const; // Умножение
	Fraction operator / (const Fraction &) const; // Деление
	 // Ниже перечислены операции сравнения
	bool operator < (const Fraction&) const;
	bool operator > (const Fraction&) const;
	bool operator <= (const Fraction&) const;
	bool operator >= (const Fraction&) const;
	bool operator == (const Fraction&) const;
	bool operator != (const Fraction&) const;

	double SeeDouble() const; // Функция для вывода дроби в формате double

	friend ostream & operator << (ostream &, const Fraction &); // Функция, нужная для реализации вывода
};