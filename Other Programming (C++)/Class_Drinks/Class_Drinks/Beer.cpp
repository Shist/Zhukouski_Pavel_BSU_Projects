#include "Beer.h"

Beer::Beer(string new_name, int new_volume, double new_alc_perc, Raw_Mat new_mat)
{
	if (new_volume <= 0 || new_volume > 2147483646)
		throw exception("Incorrect or too big entered value of volume!");
	if (new_alc_perc < 0.0 || new_alc_perc > 100.0)
		throw exception("Incorrect entered value of alcohol percents!");
	name_drink = new_name;
	tare_volume = new_volume;
	alc_perc = new_alc_perc;
	mater = new_mat;
}

Beer::~Beer()
{
}

string Beer::get_name() const
{
	return name_drink;
}

int Beer::get_volume() const
{
	return tare_volume;
}

double Beer::get_alc_perc() const
{
	return alc_perc;
}

Raw_Mat Beer::get_mater() const
{
	return mater;
}

void Beer::output_mater(ostream& out) const
{
	char mat[7];
	if (mater == Raw_Mat::Wheat)
		strcpy(mat, "Wheat");
	else if (mater == Raw_Mat::Barley)
		strcpy(mat, "Barley");
	else
		strcpy(mat, "Ginger");
	out << mat << endl;
}