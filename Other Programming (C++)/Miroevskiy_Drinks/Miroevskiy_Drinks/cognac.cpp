#include "cognac.h"
#pragma warning (disable: 4996)

std::ostream& operator << (std::ostream& out, const Excerpt& t)
{
	switch (t) {
	case Excerpt::deLuxe: return (out << "2 года");
	case Excerpt::Superior: return (out << "3 года");
	case Excerpt::Vieux: return (out << "4 года");
	case Excerpt::GrandReserve: return (out << "5 лет");
	}
	return (out);
}

Cognac::Cognac(string aname, double avolume, double apercentage, Excerpt aexcerpt) : HardDrinks(aname, avolume, apercentage)
{
	SetExcerpt(aexcerpt);
}


Excerpt Cognac::GetExcerpt() const
{
	return this->excerpt;
}

void Cognac::SetExcerpt(Excerpt aexcerpt)
{
	excerpt = aexcerpt;
}

Cognac::~Cognac()
{
	cout << "Коньяк " << this->GetName() << " выпито";
}

void Cognac::GetInfo() const
{
	HardDrinks::GetInfo();
	cout << "Степень крепости: " << GetExcerpt() << endl;
}