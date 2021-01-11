#pragma once
#include <cstring>
#include <iostream>
using namespace std;

class BottledDrinks
{
protected:
	string name;
	double volume;
	void SetName(string);
	void SetVolume(double);

public:
	BottledDrinks(string, double);
	virtual ~BottledDrinks() = 0;
	string GetName() const;
	double GetVolume() const;
	void GetInfo() const;
};