#include "lemonade.h"

std::ostream& operator << (std::ostream& out, const Taste& t)
{
	switch (t) {
	case Taste::Lemon: return (out << "Лимон");
	case Taste::Strawberry: return (out << "Клубничный");
	case Taste::Raspberry: return (out << "Малиновый");
	case Taste::Plum: return (out << "Сливовый");
	case Taste::Coke: return (out << "Кола");
	}
	return (out);
}

Lemonade::Lemonade(string aname, double avolume, Sugaric asugaric, Taste ataste) : SoftDrinks(aname, avolume, asugaric)
{
	SetTaste(ataste);
}


Taste Lemonade::GetTaste() const
{
	return this->taste;
}

void Lemonade::SetTaste(Taste ataste)
{
	taste = ataste;
}

Lemonade::~Lemonade()
{
	cout << "Лимонад " << this->GetName() << " выпит";
}

void Lemonade::GetInfo() const
{
	SoftDrinks::GetInfo();
	cout << "Вкус: " << GetTaste() << endl;
}