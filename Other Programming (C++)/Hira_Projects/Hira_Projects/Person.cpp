#pragma warning (disable : 4996)
#include "Person.h"
#include "string.h"
using namespace std;

int Person::next_ID = 0;


Person::Person(const char* aname, Gender agender, const Person* amother, const Person* afather) : ID(++next_ID) {
	if (aname == NULL)
		throw "inv NULL";
	if (aname[0] == '\0')
		throw "inv len";
	name = new char[strlen(aname) + 1];
	strcpy(name, aname);
	gender = agender;
	mother = amother;
	father = afather;
}
Person::Person(const char* aname, Gender agender, const Person* amother) : Person(aname, agender, amother, NULL) {}
Person::Person(const char* aname, Gender agender) : Person(aname, agender, NULL, NULL) {}


Person::Person(const Person& d) : ID(++next_ID) {
	Clone(d);
}
Person& Person::operator = (const Person& p)
{
	if (this != &p) {
		Erase(); Clone(p);
	}
	return *this;
}

int Person::GetID() const { return ID; }
const char* Person::GetName() const { return name; }
Person::Gender Person::GetGender() const { return gender; }
const char* Person::GetMother() const { return mother->GetName(); }
const char* Person::GetFather() const { return father->GetName(); }


void Person::Erase() {
	delete[] name;
}
void Person::Clone(const Person& p) {
	name = new char[strlen(p.name) + 1];
	strcpy(name, p.name);
	gender = p.gender;
	mother = p.mother;
	father = p.father;
}

const Person* Person::GiveBirth(const char* aname, Gender agender, const Person* afather) const {
	const Person* child = new Person(aname, agender, this, afather);
	return child;
}
const Person* Person::GiveBirth(const char* aname, Gender agender) const {
	return GiveBirth(aname, agender, NULL);
}

ostream& operator << (ostream& s, const Person& p) {
	s << "Name: " << p.GetName() << endl;
	/*s << "Gender: " << (p.GetGender() == Person::Gender::man ? "man" : "woman") << endl;
	s << "Mother: " << p.GetMother() << endl;
	s << "Father: " << p.GetFather() << endl;*/
	return s;
}


Person::~Person() {
	Erase();
}
