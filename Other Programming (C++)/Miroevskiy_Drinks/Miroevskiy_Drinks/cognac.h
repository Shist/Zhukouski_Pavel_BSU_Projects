#pragma once
#include "harddrinks.h"

enum class Excerpt
{
	deLuxe,
	Superior,
	Vieux,
	GrandReserve
};

class Cognac :
	public HardDrinks
{
private:
	string name;
	double volume;
	double percentage;
	Excerpt excerpt;
	void SetExcerpt(Excerpt);

public:
	Cognac(string, double, double, Excerpt);
	~Cognac();
	Excerpt GetExcerpt() const;
	void GetInfo() const;
};
