#include "Person.h"

int Person::next_ID = 0;
const Person Person::Adam("Adam", Gender::Male);
const Person Person::Eve("Eve", Gender::Female);

void Person::setName(const char* newName)
{
	if (newName == nullptr)
		throw exception("Invalid parameter! (NULL)");
	else if (newName[0] == '\0')
		throw exception("Invalid parameter! (empty)");
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void Person::erase()
{
	delete[] name;
}

Person::~Person()
{
	erase();
}

void Person::clone(const Person& someone)
{
	setName(someone.getName());
	(Gender&)gender = someone.getGender();
	mother = someone.getMother();
	father = someone.getFather();
}

Person::Person(const char* newName, Gender newGender) : ID(++next_ID), gender(newGender), mother(nullptr), father(nullptr)
{
	setName(newName);
}

Person::Person(const char *newName, Gender newGender, const Person* newMother, const Person* newFather) : ID(++next_ID), gender(newGender), mother(newMother), father(newFather)
{
	if (newMother == nullptr)
		throw exception("Error: invalid parameter, the person without mother.");
	else if (newMother->getGender() == Gender::Male)
		throw exception("Error: mother can't be male.");
	if (newFather != nullptr&&newFather->getGender() == Gender::Female)
		throw exception("Error: father can't be female.");
	setName(newName);
}

//Добавили гендер в список инициализации.
Person::Person(const Person& someone) : ID(++next_ID), gender(someone.getGender())
{
	clone(someone);
}

const char* Person::getName() const
{
	return name;
}

Gender Person::getGender() const
{
	return gender;
}

void Person::output_gender(ostream& out) const
{
	char gen[7];
	if (gender == Gender::Male)
		strcpy(gen, "Male");
	else
		strcpy(gen, "Female");
	out << gen << endl;
}

const Person* Person::getMother() const
{
	return mother;
}

const Person* Person::getFather() const
{
	return father;
}

int Person::getID() const
{
	return ID;
}

Person& Person::operator =(const Person& someone)
{
	//Проверка необходима для самоприсваивания
	if (this != &someone)
	{
		erase();
		clone(someone);
	}

	return *this;
}

Person* Person::giveBirth(const Person* newFather, const char* newChild_boy, const char* newChild_girl) const
{
	if (gender == Gender::Male)
		throw exception("Error: calling of giveBirth method from male object is prohibited.");
	Person* child;
	random_device generator; // Обращаемся к функции рандома
	uniform_int_distribution<int> distribution(0, 1); // Задаем интервал, среди которого будут выбираться рандомный числа (0 или 1)
	Gender gen_pol = (Gender)distribution(generator);
	if (gen_pol == Gender::Male)
		child = new Person(newChild_boy, (Gender)gen_pol, this, newFather);
	else
		child = new Person(newChild_girl, (Gender)gen_pol, this, newFather);
	return child;
}