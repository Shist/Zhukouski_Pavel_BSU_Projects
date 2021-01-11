#include "wine.h"
std::ostream& operator << (std::ostream& out, const Type& t)
{
	switch (t) {
	case Type::White: return (out << "�����");
	case Type::Red: return (out << "�������");
	case Type::Pink: return (out << "�������");
	}
	return (out);
}

std::ostream& operator << (std::ostream& out, const Sugary& t)
{
	switch (t) {
	case Sugary::Dry: return (out << "�����");
	case Sugary::Semidry: return (out << "���������");
	case Sugary::Semisweet: return (out << "�����������");
	case Sugary::Sweet: return (out << "�������");
	}
	return (out);
}

Wine::Wine(string aname, double avolume, double apercentage, Type atype, Sugary asugary) : HardDrinks(aname, avolume, apercentage)
{
	SetType(atype);
	SetSugary(asugary);
}


Type Wine::GetType() const
{
	return this->type;
}

Sugary Wine::GetSugary() const
{
	return this->sugary;
}

void Wine::SetType(Type atype)
{
	type = atype;
}

void Wine::SetSugary(Sugary asugary)
{
	sugary = asugary;
}

Wine::~Wine()
{
	cout << "���� " << this->GetName() << " ������";
}

void Wine::GetInfo() const
{
	HardDrinks::GetInfo();
	cout << "��� ����: " << GetType() << " " << GetSugary() << endl;
}