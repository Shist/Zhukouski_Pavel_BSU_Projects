#include "Client.h"

Client::Client(Route aRoute, string aFIO, unsigned int aVoucher_Count)
{
	route = aRoute;
	FIO = aFIO;
	voucher_count = aVoucher_Count;
}

Client::Client()
{
	route = Route();
	FIO = "";
	voucher_count = 0;
}

Client::~Client()
{
}

Route Client::getRoute() const
{
	return route;
}

string Client::getFIO() const
{
	return FIO;
}

unsigned int Client::getVoucher_Count() const
{
	return voucher_count;
}

double Client::Calc_Tickets_Cost()
{
	return (voucher_count * route.getPrice());
}