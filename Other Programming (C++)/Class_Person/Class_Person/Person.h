#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <exception>
#include <random>

using namespace std;

enum class Gender {
	Male,
	Female,
};

class Person
{
private:
	static int next_ID;
	const int ID;
	char *name;
	const Gender gender;
	const Person *mother;
	const Person *father;
	void setName(const char*);
	void erase();
	void clone(const Person&);
	Person(const char* newName, Gender newGender); // Только для Адама и Евы
public:
	static const Person Adam;
	static const Person Eve;
	Person(const char*, Gender, const Person*, const Person*); // Конструктор
	Person(const Person&); // Конструктор копирования
	int getID() const;
	const char* getName() const;
	Gender getGender() const;
	void output_gender(ostream& out) const; // для вывода пола
	const Person* getMother() const;
	const Person* getFather() const;
	Person& operator =(const Person&);
	Person* giveBirth(const Person* father, const char* newChild_boy, const char* newChild_girl) const;
	virtual ~Person(); // Деструктор
};