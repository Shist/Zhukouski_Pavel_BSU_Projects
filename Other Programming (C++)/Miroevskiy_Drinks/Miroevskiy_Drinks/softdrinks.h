#pragma once
#include "bottleddrinks.h"

enum class Sugaric
{
	None,
	Some
};

class SoftDrinks :
	public BottledDrinks
{
protected:

	Sugaric sugaric;
	void SetSugaric(Sugaric);

public:
	SoftDrinks(string, double, Sugaric);
	virtual ~SoftDrinks() = 0;
	Sugaric GetSugaric() const;
	void GetInfo() const;
};
