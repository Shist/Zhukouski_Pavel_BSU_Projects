#include "Route.h"

Route::Route(string aCountry, voucher_type* aVoucher, double aPrice)
{
	country = aCountry;
	voucher = aVoucher;
	price = aPrice;
}

Route::Route()
{
	country = "";
	voucher = nullptr;
	price = 0.0;
}

Route::~Route()
{
}

string Route::getCountry() const
{
	return country;
}

string Route::getVoucher() const
{
	return voucher_type_value[*(voucher)];
}

double Route::getPrice() const
{
	return price;
}