#pragma once
#include "Bottled_Drinks.h"

class Alcoholic_Drinks :
	public Bottled_Drinks // наследуем от класса "Ѕутилированные напитки"
{
protected:
	double alc_perc; // поле, хран€ющее информацию о содержании спирта в напитке (в процентах)
public:
	Alcoholic_Drinks(); // конструктор (пустышка)
	virtual ~Alcoholic_Drinks(); // виртуальный деструктор
	virtual double get_alc_perc() const = 0; // виртуальный геттер (процент алкогол€)
};