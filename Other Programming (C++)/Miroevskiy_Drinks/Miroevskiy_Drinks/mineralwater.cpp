#include "mineralwater.h"

std::ostream& operator << (std::ostream& out, const Carbonated& t)
{
	switch (t) {
	case Carbonated::Still: return (out << "Негазированная");
	case Carbonated::Sparkled: return (out << "Газированный");
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
	cout << "Минералка " << this->GetName() << " выпита";
}

void MineralWater::GetInfo() const
{
	SoftDrinks::GetInfo();
	cout << "Интенсивность пузырьков: " << GetCarbonated() << endl;
}