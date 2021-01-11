#pragma once
#include "softdrinks.h"

enum class Carbonated
{
	Still,
	Sparkled
};

class MineralWater :
	public SoftDrinks
{
	string name;
	double volume;
	Sugaric sugaric;
	Carbonated carbonated;
	void SetCarbonated(Carbonated);

public:
	MineralWater(string, double, Sugaric, Carbonated);
	~MineralWater();
	Carbonated GetCarbonated() const;
	void GetInfo() const;
};
