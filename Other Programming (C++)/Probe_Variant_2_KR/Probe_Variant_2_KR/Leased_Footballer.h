#pragma once
#include "Footballer.h"

class Leased_FootballerException
	: public FootballerException {
public:
	Leased_FootballerException(const char* message)
		: FootballerException(message) {}
};


class Leased_Footballer :
	public Footballer
{
private:
	string RentalClub = "";
	string RentalEndDate = "";
public:
	Leased_Footballer(static int anext_ID, const int aID, string aFIO, string aBirthDate, Specialization aSpec = Specialization::striker,
		string aFootballClub = "", string aContractExpDate = "", int aGamesNum = 0, double anAverRate = 0.0, string aRentalClub = "", string aRentalEndDate = "")
		:Footballer(anext_ID, aID, aFIO, aBirthDate, aSpec, aFootballClub, aContractExpDate, aGamesNum, anAverRate), 
		RentalClub(aRentalClub), RentalEndDate(aRentalEndDate) { }
	virtual ~Leased_Footballer();

	string GetRentalClub() const;
	string GetRentalEndDate() const;
};