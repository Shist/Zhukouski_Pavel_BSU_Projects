#pragma once
#include "Soft_Drinks.h"

enum class Carbonated
{
	Still,
	Sparkled
};

class Mineral_Water :
	public Soft_Drinks // наследуем от класса "Безалкогольные напитки"
{
private:
	Carbonated carb;
public:
	Mineral_Water(string, int, int, Carbonated); // конструктор для минералки (название, объем в мл, срок годности)
	virtual ~Mineral_Water(); // виртуальный деструктор
	string get_name() const; // геттер (возвращает название минералки)
	int get_volume() const; // геттер (возвращает объем минералки)
	int get_exp_date() const; // геттер (возвращает информацию о сроке годности в днях)
	void set_exp_date(int); // сеттер для изменения информации о оставшемся сроке годности того или иного напитка
	Carbonated get_carb() const; // геттер (возвращает вид минералки)
};