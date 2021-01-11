#include "beer.h"
#pragma warning (disable: 4996)

std::ostream& operator << (std::ostream& out, const RawMaterial& t)
{
	switch (t) {
	case RawMaterial::Ginger: return (out << "������");
	case RawMaterial::Weed: return (out << "�������");
	case RawMaterial::Barley: return (out << "������");
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
	cout << "���� " << this->GetName() << " ������";
}

void Beer::GetInfo() const
{
	HardDrinks::GetInfo();
	cout << "��� �����: " << GetRawMaterial() << endl;
}