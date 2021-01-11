#define _CRT_SECURE_NO_WARNING
#pragma warning (disable: 4996)
#include "bottleddrinks.h"

BottledDrinks::BottledDrinks(string aname, double avolume)
{
	SetName(aname);
	SetVolume(avolume);
}

string BottledDrinks::GetName() const
{
	return this->name;
}

double BottledDrinks::GetVolume() const
{
	return this->volume;
}

void BottledDrinks::SetName(string aname)
{
	if (aname.empty())
		throw runtime_error("\n����������� ��� �������!");
	name = aname;
}

void BottledDrinks::SetVolume(double avolume)
{
	if (avolume <= 0)
		throw runtime_error("\n����� ������� ������ ��������� ����!");
	volume = avolume;
}

BottledDrinks::~BottledDrinks()
{

}

void BottledDrinks::GetInfo() const
{
	cout << "�������� �������: " << GetName() << endl;
	cout << "����� ����: " << GetVolume() << endl;
}