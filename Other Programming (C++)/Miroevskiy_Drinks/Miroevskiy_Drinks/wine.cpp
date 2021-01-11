#include "wine.h"
std::ostream& operator << (std::ostream& out, const Type& t)
{
	switch (t) {
	case Type::White: return (out << "Белое");
	case Type::Red: return (out << "Красное");
	case Type::Pink: return (out << "Розовое");
	}
	return (out);
}

std::ostream& operator << (std::ostream& out, const Sugary& t)
{
	switch (t) {
	case Sugary::Dry: return (out << "сухое");
	case Sugary::Semidry: return (out << "полусухое");
	case Sugary::Semisweet: return (out << "полусладкое");
	case Sugary::Sweet: return (out << "сладкое");
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
	cout << "Вино " << this->GetName() << " выпито";
}

void Wine::GetInfo() const
{
	HardDrinks::GetInfo();
	cout << "Вид вина: " << GetType() << " " << GetSugary() << endl;
}