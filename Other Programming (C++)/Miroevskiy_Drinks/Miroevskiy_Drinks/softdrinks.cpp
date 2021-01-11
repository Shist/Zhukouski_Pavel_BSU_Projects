#include "softdrinks.h"
#pragma warning (disable: 4996)

std::ostream& operator << (std::ostream& out, const Sugaric& t)
{
	switch (t) {
	case Sugaric::Some: return (out << "есть");
	case Sugaric::None: return (out << "нет");
	}
	return (out);
}

SoftDrinks::SoftDrinks(string aname, double avolume, Sugaric asugaric) : BottledDrinks(aname, avolume)
{
	SetSugaric(asugaric);
}


Sugaric SoftDrinks::GetSugaric() const
{
	return this->sugaric;
}

void SoftDrinks::SetSugaric(Sugaric asugaric)
{
	sugaric = asugaric;
}

SoftDrinks::~SoftDrinks()
{

}

void SoftDrinks::GetInfo() const
{
	BottledDrinks::GetInfo();
	cout << "Наличие сахара: " << GetSugaric() << endl;
}
