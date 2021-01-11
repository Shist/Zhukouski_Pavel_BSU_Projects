#include "lemonade.h"

std::ostream& operator << (std::ostream& out, const Taste& t)
{
	switch (t) {
	case Taste::Lemon: return (out << "�����");
	case Taste::Strawberry: return (out << "����������");
	case Taste::Raspberry: return (out << "���������");
	case Taste::Plum: return (out << "��������");
	case Taste::Coke: return (out << "����");
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
	cout << "������� " << this->GetName() << " �����";
}

void Lemonade::GetInfo() const
{
	SoftDrinks::GetInfo();
	cout << "����: " << GetTaste() << endl;
}