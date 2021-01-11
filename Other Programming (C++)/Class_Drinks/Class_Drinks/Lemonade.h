#pragma once
#include "Soft_Drinks.h"

enum class Taste
{ // Виды лемонада
	Lemon,
	Strawberry,
	Raspberry,
	Plum,
	Coke
};

class Lemonade :
	public Soft_Drinks // наследуем от класса "Безалкогольные напитки"
{
private:
	Taste tast;
public:
	Lemonade(string, int, int, Taste); // конструктор для лимонада (название, объем в мл, срок годности, вид)
	virtual ~Lemonade(); // виртуальный деструктор
	string get_name() const; // геттер (возвращает название лимонада)
	int get_volume() const; // геттер (возвращает объем лимонада)
	int get_exp_date() const; // геттер (возвращает информацию о сроке годности в днях)
	void set_exp_date(int); // сеттер для изменения информации о оставшемся сроке годности того или иного напитка
	Taste get_tast() const; // геттер (возвращает вкус лемонада)
};