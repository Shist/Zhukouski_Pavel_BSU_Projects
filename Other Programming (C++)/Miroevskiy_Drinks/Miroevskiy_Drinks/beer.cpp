#include "beer.h"
#pragma warning (disable: 4996)

std::ostream& operator << (std::ostream& out, const RawMaterial& t)
{
	switch (t) {
	case RawMaterial::Ginger: return (out << "»мбирь");
	case RawMaterial::Weed: return (out << "ѕшеница");
	case RawMaterial::Barley: return (out << "ячмень");
	}
	return (out);
}

Beer::Beer(string aname, double avolume, double apercentage, RawMaterial arawmaterial) : HardDrinks(aname, avolume, apercentage)
{
	SetRawMaterial(arawmaterial);
}


RawMaterial Beer::GetRawMaterial() const
{
	return this->rawmaterial;
}

void Beer::SetRawMaterial(RawMaterial arawmaterial)
{
	rawmaterial = arawmaterial;
}

Beer::~Beer()
{
	cout << "ѕиво " << this->GetName() << " выпито";
}

void Beer::GetInfo() const
{
	HardDrinks::GetInfo();
	cout << "¬ид сырь€: " << GetRawMaterial() << endl;
}