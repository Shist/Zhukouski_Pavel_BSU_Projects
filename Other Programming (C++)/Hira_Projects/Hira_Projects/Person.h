#pragma once
#include<iostream>
#include<cstring>
#pragma warning (disable : 4996)

using namespace std;
class Person
{

public:
	enum class Gender {
		man = 0,
		woman
	};
private:
	char* name;
	static int next_ID;
	const int ID;
	Gender gender;
	const Person* mother;
	const Person* father;
	void Erase();
	void Clone(const Person&);
public:
	Person(const char*, Gender, const Person*, const Person*);
	Person(const char*, Gender, const Person*);
	Person(const char*, Gender);
	Person(const Person&);
	Person();

	int GetID() const;
	const char* GetName() const;
	Gender GetGender() const;
	const char* GetMother() const;
	const char* GetFather() const;

	const Person* GiveBirth(const char*, Gender, const Person*) const;
	const Person* GiveBirth(const char*, Gender) const;

	friend ostream& operator << (ostream&, const Person&);

	Person& operator = (const Person&);
	virtual ~Person();
};