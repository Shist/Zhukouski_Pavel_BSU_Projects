#include "Mineral_Water.h"

Mineral_Water::Mineral_Water(string new_name, int new_volume, int new_exp_date, Carbonated new_carb)
{
	if (new_volume <= 0 || new_volume > 2147483646)
		throw exception("Incorrect or too big entered value of volume!");
	if (new_exp_date <= 0 || new_exp_date > 2147483646)
		throw exception("Incorrect or too big entered value of expiration date!");
	name_drink = new_name;
	tare_volume = new_volume;
	exp_date = new_exp_date;
	carb = new_carb;
}

Mineral_Water::~Mineral_Water()
{
}

string Mineral_Water::get_name() const
{
	return name_drink;
}

int Mineral_Water::get_volume() const
{
	return tare_volume;
}

int Mineral_Water::get_exp_date() const
{
	return exp_date;
}

void Mineral_Water::set_exp_date(int new_exp_date)
{
	if (new_exp_date > exp_date || new_exp_date < 0)
		throw exception("Incorrect new entered value of expiration date!");
	exp_date = new_exp_date;
}

Carbonated Mineral_Water::get_carb() const
{
	return carb;
}