#pragma once
#include "beer.h"
#include <cstring>
#include <iostream>
using namespace std;

class Drinker
{
private:
	int age;
	int capacity;
	int your_capacity;
	void SetAge(int);

public:
	Drinker(int);
	int GetAge() const;
	void Drink(BottledDrinks*);
	~Drinker();
};
