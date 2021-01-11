#pragma once
#include<iostream>
#include<string>
#include<exception>
#pragma warning (disable: 4996)

using namespace std;

enum class Race { man, gnome, elf, other };
enum class State { normal, ill, poison, dead };
enum class Gender { man, woman };

class GameException
	: public exception {
public:
	GameException(const char *message)
		: exception(message) {}
};

class Game
{
private:
	string name;
	static int next_ID;
	const int ID;
	Gender gender;
	State state = State::normal;
	Race race;
	int age = 0;
	int health = 0;
	int MAX_health = 0;
	int skill = 0;

	void Clone(Game&);
public:
	Game(string aname, Race arace, Gender agender, State astate = State::normal,
		int anage = 0, int ahealth = 0, int askill = 0) :
		name(aname), state(astate),
		race(arace), gender(agender), age(anage),
		health(ahealth), MAX_health(ahealth), skill(askill),
		ID(next_ID++) {
		if (aname.empty())
			throw GameException("Can't have an empty name for person");
		if (anage < 0)
			throw GameException("Age can't be < 0");
		if (ahealth < 0)
			throw GameException("Health can't be < 0");
		if (askill < 0)
			throw GameException("Skill can't be < 0");
	}
	Game(Game&);
	virtual ~Game();

	string GetName();
	const int GetID();
	Gender GetGender();
	State GetState();
	Race GetRace();
	int GetAge();
	int GetHealth();
	const int GetMAX_health();
	int GetSkill();

	Game& operator = (Game&);

	void ChangeStateTo(State);
	void ChangeAgeTo(int);
	void ChangeHealthTo(int);
	void ChangeMAX_healthTo(int);
	void ChangeSkillTo(int);

	friend ostream& operator << (ostream&, Game&);

	bool CompareHealth(string, Game&);
	bool CompareSkill(string, Game&);
};