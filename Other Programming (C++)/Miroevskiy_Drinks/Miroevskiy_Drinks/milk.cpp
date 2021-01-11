#include "milk.h"
Milk::Milk(string aname, double avolume, Sugaric asugaric, double afatcontent) : SoftDrinks(aname, avolume, asugaric)
{
	SetFatContent(afatcontent);
}


double Milk::GetFatContent() const
{
	return this->fatcontent;
}

void Milk::SetFatContent(double afatcontent)
{
	fatcontent = afatcontent;
}

Milk::~Milk()
{
	cout << "������ " << this->GetName() << " ������";
}

void Milk::GetInfo() const
{
	SoftDrinks::GetInfo();
	cout << "��������: " << GetFatContent() << endl;
}