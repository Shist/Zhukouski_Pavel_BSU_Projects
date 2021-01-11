#pragma once
#include<iostream>
#include<string>
#include<exception>
#pragma warning (disable: 4996)

using namespace std;

enum class Specialization { goalkeeper, defender, midfielder, striker };

class FootballerException
	: public exception {
public:
	FootballerException(const char *message)
		: exception(message) {}
};

class Footballer
{
private:
	static int next_ID;
	const int ID;
	string FIO;
	string BirthDate;
	Specialization Spec = Specialization::striker;
	string FootballClub = "";
	string ContractExpDate = "";
	int GamesNum = 0;
	double AverRate = 0.0; // Сдалала не массив игр с рейтингами, а хотя бы просто среднее значение этого рейтинг

	void Clone(Footballer&);
public:
	Footballer(static int anext_ID, const int aID, string aFIO, string aBirthDate, Specialization aSpec = Specialization::striker,
	string aFootballClub = "", string aContractExpDate = "", int aGamesNum = 0, double anAverRate = 0.0) : FIO(aFIO), BirthDate(aBirthDate), Spec(aSpec), 
		FootballClub(aFootballClub), ContractExpDate(aContractExpDate), GamesNum(aGamesNum), AverRate(anAverRate), ID(next_ID++)
	{
		if (FIO.empty())
			throw FootballerException("The name of the footballer can't be empty!");
		if (GamesNum < 0)
			throw FootballerException("The number of games of the footballer can't be < 0!");
		if (AverRate < 0.0)
			throw FootballerException("Avreage rate can't be < 0!");
	}
	Footballer(Footballer&);
	virtual ~Footballer();

	const int GetID() const;
	string GetFIO() const;
	string GetBirthDate() const;
	Specialization GetSpec() const;
	string GetFootballClub() const;
	string GetContractExpDate() const;
	int GetGamesNum() const;
	double GetAverRate() const;

	void NewSeason();
	void NewGame(int GameRate);

	Footballer& operator = (Footballer&);

	bool CompareGamesNum(string, Footballer&);
	bool CompareAverRate(string, Footballer&);

	friend ostream& operator << (ostream&, Footballer&);
};