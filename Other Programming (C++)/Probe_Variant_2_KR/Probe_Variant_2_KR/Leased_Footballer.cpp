#include "Leased_Footballer.h"

#pragma warning (disable : 4996)

using namespace std;

Leased_Footballer::~Leased_Footballer() {}

string Leased_Footballer::GetRentalClub() const { return RentalClub; };

string Leased_Footballer::GetRentalEndDate() const { return RentalEndDate; };