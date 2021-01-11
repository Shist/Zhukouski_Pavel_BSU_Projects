#pragma once
#include "Bottled_Drinks.h"

class Soft_Drinks :
	public Bottled_Drinks // наследуем от класса "Бутилированные напитки"
{
protected:
	int exp_date; // поле, хранящее информацию о сроке годности напитка в днях после его производства
public:
	Soft_Drinks(); // конструктор (пустышка)
	virtual ~Soft_Drinks(); // виртуальный деструктор
	virtual int get_exp_date() const = 0; // виртуальный геттер (срок годности)
	virtual void set_exp_date(int) = 0; // виртуальный сеттер для изменения информации о оставшемся сроке годности того или иного напитка
};