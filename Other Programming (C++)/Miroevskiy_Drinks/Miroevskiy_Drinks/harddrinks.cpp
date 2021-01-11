#include "harddrinks.h"
#pragma warning (disable: 4996)

HardDrinks::HardDrinks(string aname, double avolume, double apercentage) : BottledDrinks(aname, avolume)
{
	SetPercentage(apercentage);
}


double HardDrinks::GetPercentage() const
{
	return this->percentage;
}

void HardDrinks::SetPercentage(double apercentage)
{
	if (apercentage <= 0)
		throw runtime_error("Напиток безалкогольный!");
	if (apercentage > 100)
		throw runtime_error("Количество процентов не должно превышать сто!");
	percentage = apercentage;
}

HardDrinks::~HardDrinks()
{

}

void HardDrinks::GetInfo() const
{
	BottledDrinks::GetInfo();
	cout << "Процент алкоголя: " << GetPercentage() << endl;
}