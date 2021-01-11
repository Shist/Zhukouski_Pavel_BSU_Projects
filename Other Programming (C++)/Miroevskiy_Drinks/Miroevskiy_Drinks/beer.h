#pragma once
#include "harddrinks.h"

enum class RawMaterial
{
	Ginger,
	Weed,
	Barley
};

class Beer :
	public HardDrinks
{
private:
	string name;
	double volume;
	double percentage;
	RawMaterial rawmaterial;
	void SetRawMaterial(RawMaterial);

public:
	Beer(string, double, double, RawMaterial);
	~Beer();
	RawMaterial GetRawMaterial() const;
	void GetInfo() const;
};
