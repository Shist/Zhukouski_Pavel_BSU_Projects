#pragma once
#include <exception>
#include <cmath>
#include <iostream>
#include <sstream>
#define PI 3.143159265358
using namespace std;

class Point2D
{
private: // Те методы и те поля, с которыми работает только создатель класса
	double x, y;
public: // Те методы и те поля, к которым может обращаться пользователь класса
	Point2D(double = 0, double = 0);
	virtual ~Point2D();
	double getx() const;
	void setx(double);
	double gety() const;
	void sety(double);
	double getRo() const;
	double getPhi() const;
	Point2D operator - () const; // унарный минус
	Point2D& operator ++ (); // инкремент(префиксный)
	Point2D operator ++ (int); // инкремент(постфиксный)
	Point2D operator + (const Point2D&) const; // сложение
	double operator * (const Point2D&) const;
	bool operator == (const Point2D&) const; // Сложение (равно)
	bool operator != (const Point2D&) const; // Сложение (не равно)
	Point2D operator * (double) const; // Умножение на число
	friend Point2D operator * (double, const Point2D&); // Умножение на число (это для реализации коммутативности)
	friend ostream& operator << (ostream&, const Point2D&); // РЕАЛИЗАЦИЯ ВЫВОДА В ПОТОК!!!
	string toString() const; // Альтернатива выводу в поток
	operator double();
	virtual double Module();
};
// Операции над классом Point2D
// 1) Сложение и вычитание точек (по правилам сложения и вычитания векторов);
// 2) Унарный минус (по правилам векторов);
// 3) Умножение точки на число и числа на точку (результат - растяжение или сжатие точки);
// 4) Умножение двух точек(результат – скалярное произведение);
// 5) Инкремент и декремент точки(результат – увеличение или уменьшение координат на 1);
// 6) Сравнение на равенство и неравенство двух точек.)