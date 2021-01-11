#pragma once
#include "harddrinks.h"

enum class Type
{
	White,
	Red,
	Pink
};

enum class Sugary
{
	Dry,
	Semidry,
	Semisweet,
	Sweet
};

class Wine :
	public HardDrinks
{
private:
	string name;
	double volume;
	double percentage;
	Type type;
	Sugary sugary;
	void SetType(Type);
	void SetSugary(Sugary);

public:
	Wine(string, double, double, Type, Sugary);
	~Wine();
	Type GetType() const;
	Sugary GetSugary() const;
	void GetInfo() const;
};
