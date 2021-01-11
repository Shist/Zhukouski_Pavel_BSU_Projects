#pragma once
#include "Alcoholic_Drinks.h"

enum class Color // виды вина
{
	White, // белое
	Red // красное
};

class Wine :
	public Alcoholic_Drinks // наследуем от класса "Алкогольные напитки"
{
private:
	Color colour; // цвет вина
public:
	Wine(string, int, double, Color); // конструктор для вина (название, объем в мл, процент спирта, цвет)
	virtual ~Wine(); // виртуальный деструктор
	string get_name() const; // геттер (возвращает название вина)
	int get_volume() const; // геттер (возвращает объем вина)
	double get_alc_perc() const; // геттер (возвращает процент алкоголя в вине)
	Color get_colour() const; // геттер для цвета вина (его вывести в поток так просто не получится)
	void output_colour(ostream& out) const; // для вывода вида вина в поток
};