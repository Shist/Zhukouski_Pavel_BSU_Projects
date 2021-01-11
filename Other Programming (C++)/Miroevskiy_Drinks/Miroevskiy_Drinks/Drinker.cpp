#define _CRT_SECURE_NO_WARNING
#pragma warning (disable: 4996)
#include "Drinker.h"

Drinker::Drinker(int anage)
{
	SetAge(anage);

}



Drinker::~Drinker()
{
	cout << endl << " Вы покидаете бар..." << endl;
}

int Drinker::GetAge() const
{
	return this->age;
}

void Drinker::Drink(BottledDrinks*)
{
}

void Drinker::SetAge(int anage)
{
	if (anage <= 0)
		throw runtime_error("\nВозраст посетителя - натуральное число!");
	age = anage;
}
