#include "Cognac.h"

Cognac::Cognac(string new_name, int new_volume, double new_alc_perc, Excerpt new_Excerpt)
{
	if (new_volume <= 0 || new_volume > 2147483646)
		throw exception("Incorrect or too big entered value of volume!");
	if (new_alc_perc < 0.0 || new_alc_perc > 100.0)
		throw exception("Incorrect entered value of alcohol percents!");
	name_drink = new_name;
	tare_volume = new_volume;
	alc_perc = new_alc_perc;
	exc = new_Excerpt;
}

Cognac::~Cognac()
{
}

string Cognac::get_name() const
{
	return name_drink;
}

int Cognac::get_volume() const
{
	return tare_volume;
}

double Cognac::get_alc_perc() const
{
	return alc_perc;
}

Excerpt Cognac::get_exc() const
{
	return exc;
}