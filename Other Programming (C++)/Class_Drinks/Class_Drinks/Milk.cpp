#include "Milk.h"

Milk::Milk(string new_name, int new_volume, double new_fat_perc, int new_exp_date)
{
	if (new_volume <= 0 || new_volume > 2147483646)
		throw exception("Incorrect or too big entered value of volume!");
	if (new_fat_perc < 0.0 || new_fat_perc > 100.0)
		throw exception("Incorrect entered value of fat percents!");
	if (new_exp_date <= 0 || new_exp_date > 2147483646)
		throw exception("Incorrect or too big entered value of expiration date!");
	name_drink = new_name;
	tare_volume = new_volume;
	fat_perc = new_fat_perc;
	exp_date = new_exp_date;
}

Milk::~Milk()
{
}

string Milk::get_name() const
{
	return name_drink;
}

int Milk::get_volume() const
{
	return tare_volume;
}

double Milk::get_fat_perc() const
{
	return fat_perc;
}

int Milk::get_exp_date() const
{
	return exp_date;
}

void Milk::set_exp_date(int new_exp_date)
{
	if (new_exp_date > exp_date || new_exp_date < 0)
		throw exception("Incorrect new entered value of expiration date!");
	this->exp_date = new_exp_date;
}