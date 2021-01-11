#include "Footballer.h"
#pragma warning (disable : 4996)

using namespace std;

int Footballer::next_ID = 0;


void Footballer::Clone(Footballer& g) {
	FIO = g.FIO;
	BirthDate = g.BirthDate;
	Spec = g.Spec;
	FootballClub = g.FootballClub;
	ContractExpDate = g.ContractExpDate;
	GamesNum = g.GamesNum;
}

Footballer::Footballer(Footballer& g) : ID(++next_ID) {
	Clone(g);
}

Footballer::~Footballer() { /*Если бы создавали динамический массив, то удаляли бы тут*/ }

const int Footballer::GetID() const { return ID; };
string Footballer::GetFIO() const { return FIO; };
string Footballer::GetBirthDate() const { return BirthDate; };
Specialization Footballer::GetSpec() const { return Spec; };
string Footballer::GetFootballClub() const { return FootballClub; };
string Footballer::GetContractExpDate() const { return ContractExpDate; };
int Footballer::GetGamesNum() const { return GamesNum; };
double Footballer::GetAverRate() const { return AverRate; };

void Footballer::NewSeason()
{
	FootballClub = "";
	ContractExpDate = "";
	GamesNum = 0;
	AverRate = 0.0;
}

void Footballer::NewGame(int GameRate)
{
	if (GameRate < 1 || GameRate > 10)
		throw FootballerException("Incorrect Game Rate!");
	AverRate *= GamesNum;
	GamesNum++;
	AverRate += GameRate;
	AverRate /= GamesNum;
}

Footballer& Footballer::operator=(Footballer& g) {
	if (this != &g)
		Clone(g);
	return *this;
}

bool Footballer::CompareGamesNum(string s, Footballer& g) {
	if (s == ">")
		return (GetGamesNum() > g.GetGamesNum());
	else if (s == "<")
		return (GetGamesNum() < g.GetGamesNum());
	else if (s == ">=")
		return (GetGamesNum() >= g.GetGamesNum());
	else if (s == "<=")
		return (GetGamesNum() <= g.GetGamesNum());
	else if (s == "=")
		return (GetGamesNum() == g.GetGamesNum());
	else if (s == "!=")
		return (GetGamesNum() != g.GetGamesNum());
	else
		throw FootballerException("Incorrect parameter for GamesNum comparison entered!");
}
bool Footballer::CompareAverRate(string s, Footballer& g) {
	if (s == ">")
		return (GetAverRate() > g.GetAverRate());
	else if (s == "<")
		return (GetAverRate() < g.GetAverRate());
	else if (s == ">=")
		return (GetAverRate() >= g.GetAverRate());
	else if (s == "<=")
		return (GetAverRate() <= g.GetAverRate());
	else if (s == "=")
		return (GetAverRate() == g.GetAverRate());
	else if (s == "!=")
		return (GetAverRate() != g.GetAverRate());
	else
		throw FootballerException("Incorrect parameter for average rate comparison entered!");
}

ostream& operator << (ostream& s, Footballer& g) {
	s << "ID: " << g.GetID() << endl;
	s << "FIO: " << g.GetFIO() << endl;
	s << "BirthDate: " << g.GetBirthDate() << endl;
	s << "Spec: " <<
		(g.GetSpec() == Specialization::defender ? "defender" :
		(g.GetSpec() == Specialization::goalkeeper ? "goalkeeper" :
			g.GetSpec() == Specialization::midfielder ? "midfielder" : "striker")) << endl;
	s << "Football Club: " << g.GetFootballClub() << endl;
	s << "Contract Exp Date: " << g.GetContractExpDate() << endl;
	s << "Number of the games: " << g.GetGamesNum() << endl;
	s << "Average Rate in season: " << g.GetAverRate() << endl;
	return s;
}