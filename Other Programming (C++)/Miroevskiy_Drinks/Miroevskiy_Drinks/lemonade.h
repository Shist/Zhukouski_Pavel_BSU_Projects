#pragma once
#include "softdrinks.h"

enum class Taste
{
	Lemon,
	Strawberry,
	Raspberry,
	Plum,
	Coke
};

class Lemonade :
	public SoftDrinks
{
	string name;
	double volume;
	Sugaric sugaric;
	Taste taste;
	void SetTaste(Taste);

public:
	Lemonade(string, double, Sugaric, Taste);
	~Lemonade();
	Taste GetTaste() const;
	void GetInfo() const;
};
