#include "mineralwater.h"

std::ostream& operator << (std::ostream& out, const Carbonated& t)
{
	switch (t) {
	case Carbonated::Still: return (out << "��������������");
	case Carbonated::Sparkled: return (out << "������������");
	}
	return (out);
}

MineralWater::MineralWater(string aname, double avolume, Sugaric asugaric, Carbonated acarbonated) : SoftDrinks(aname, avolume, asugaric)
{
	SetCarbonated(acarbonated);
}


Carbonated MineralWater::GetCarbonated() const
{
	return this->carbonated;
}

void MineralWater::SetCarbonated(Carbonated acarbonated)
{
	carbonated = acarbonated;
}

MineralWater::~MineralWater()
{
	cout << "��������� " << this->GetName() << " ������";
}

void MineralWater::GetInfo() const
{
	SoftDrinks::GetInfo();
	cout << "������������� ���������: " << GetCarbonated() << endl;
}