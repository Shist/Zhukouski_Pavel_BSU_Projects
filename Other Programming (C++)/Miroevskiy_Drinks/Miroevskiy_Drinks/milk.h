#pragma once
#include "softdrinks.h"
class Milk :
	public SoftDrinks
{
private:
	string name;
	double volume;
	Sugaric sugaric;
	double fatcontent;
	void SetFatContent(double);

public:
	Milk(string, double, Sugaric, double);
	~Milk();
	double GetFatContent() const;
	void GetInfo() const;
};
