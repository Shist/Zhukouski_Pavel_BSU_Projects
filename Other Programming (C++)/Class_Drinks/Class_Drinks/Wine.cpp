#include "Wine.h"

Wine::Wine(string new_name, int new_volume, double new_alc_perc, Color new_col)
{
	if (new_volume <= 0 || new_volume > 2147483646)
		throw exception("Incorrect or too big entered value of volume!");
	if (new_alc_perc < 0.0 || new_alc_perc > 100.0)
		throw exception("Incorrect entered value of alcohol percents!");
	name_drink = new_name;
	tare_volume = new_volume;
	alc_perc = new_alc_perc;
	colour = new_col;
}

Wine::~Wine()
{
}

string Wine::get_name() const
{
	return name_drink;
}

int Wine::get_volume() const
{
	return tare_volume;
}

double Wine::get_alc_perc() const
{
	return alc_perc;
}

Color Wine::get_colour() const
{
	return colour;
}

void Wine::output_colour(ostream& out) const
{
	char col[6];
	if (colour == Color::White)
		strcpy(col, "White");
	else 
		strcpy(col, "Red");
	out << col << endl;
}