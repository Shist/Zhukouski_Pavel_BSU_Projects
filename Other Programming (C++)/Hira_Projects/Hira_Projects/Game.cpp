#include "Game.h"
#pragma warning (disable : 4996)

using namespace std;

int Game::next_ID = 0;


void Game::Clone(Game& g) {
	name = g.name;
	state = g.state;
	race = g.race;
	gender = g.gender;
	age = g.age;
	health = g.health;
	MAX_health = g.MAX_health;
}

Game::Game(Game& g) : ID(++next_ID) {
	Clone(g);
}

Game::~Game() {}

string Game::GetName() { return name; }
const int Game::GetID() { return ID; }
Gender Game::GetGender() { return gender; }
State Game::GetState() { return state; }
Race Game::GetRace() { return race; }
int Game::GetAge() { return age; }
int Game::GetHealth() { return health; }
const int Game::GetMAX_health() { return MAX_health; }
int Game::GetSkill() { return skill; }

Game& Game::operator=(Game& g) {
	if (this != &g)
		Clone(g);
	return *this;
}

void Game::ChangeAgeTo(int newage) {
	if (newage < age)
		throw GameException("We can't change age to less than we have");
	age = newage;
}
void Game::ChangeStateTo(State newstate) {
	state = newstate;
}
void Game::ChangeHealthTo(int newhealth) {
	if (newhealth > MAX_health)
		throw GameException("We can't add more than MAX_health");
	if (newhealth < 0)
		throw GameException("We can't change health to < 0");
	health = newhealth;
}
void Game::ChangeMAX_healthTo(int newMAX_health) {
	if (newMAX_health < health)
		throw GameException("We can't change MAX_health to less than health");
	MAX_health = newMAX_health;
}
void Game::ChangeSkillTo(int newskill) {
	if (newskill < skill)
		throw GameException("We can't change skill to less than we have");
	skill = newskill;
}

bool Game::CompareHealth(string s, Game& g) {
	if (s == ">")
		return (GetHealth() / GetMAX_health() > g.GetHealth() / g.GetMAX_health());
	else if (s == "<")
		return (GetHealth() / GetMAX_health() < g.GetHealth() / g.GetMAX_health());
	else if (s == ">=")
		return (GetHealth() / GetMAX_health() >= g.GetHealth() / g.GetMAX_health());
	else if (s == "<=")
		return (GetHealth() / GetMAX_health() < +g.GetHealth() / g.GetMAX_health());
	else if (s == "=")
		return (GetHealth() / GetMAX_health() == g.GetHealth() / g.GetMAX_health());
	else if (s == "!=")
		return (GetHealth() / GetMAX_health() != g.GetHealth() / g.GetMAX_health());
}
bool Game::CompareSkill(string s, Game& g) {
	if (s == ">")
		return GetSkill() > g.GetSkill();
	else if (s == "<")
		return GetSkill() < g.GetSkill();
	else if (s == ">=")
		return GetSkill() >= g.GetSkill();
	else if (s == "<=")
		return GetSkill() < +g.GetSkill();
	else if (s == "=")
		return GetSkill() == g.GetSkill();
	else if (s == "!=")
		return GetSkill() != g.GetSkill();
}





ostream& operator << (ostream& s, Game& g) {
	s << "Name: " << g.GetName() << endl;
	s << "Gender: " << (g.GetGender() == Gender::man ? "man" : "woman") << endl;
	s << "State: " <<
		(g.GetState() == State::normal ? "normal" :
		(g.GetState() == State::ill ? "ill" :
			g.GetState() == State::poison ? "poison" : "dead")) << endl;
	s << "Race: " <<
		(g.GetRace() == Race::man ? "man" :
		(g.GetRace() == Race::gnome ? "gnome" :
			g.GetRace() == Race::elf ? "elf" : "other")) << endl;
	s << "Age: " << g.GetAge() << endl;
	s << "Health / MAX_health: " << g.GetHealth() << " / " << g.GetMAX_health() << endl;
	s << "Skill: " << g.GetSkill() << endl;
	return s;
}