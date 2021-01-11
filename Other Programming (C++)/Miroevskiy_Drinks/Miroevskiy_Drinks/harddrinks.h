#pragma once
#include "bottleddrinks.h"

class HardDrinks :
	public BottledDrinks
{
protected:

	double percentage;
	void SetPercentage(double);

public:
	HardDrinks(string, double, double);
	virtual ~HardDrinks() = 0;
	double GetPercentage() const;
	void GetInfo() const;
};
