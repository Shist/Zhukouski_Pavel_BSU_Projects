#include <iostream>
#include "Client.h"
using namespace std;

int main()
{
	string my_country = "Belarus";
	voucher_type* my_voucher = new voucher_type(excursion);
	double my_price = 1440.27;
	Route my_route(my_country, my_voucher, my_price);
	string my_FIO = "Podgol Vadim Ivanovich";
	unsigned int my_voucher_count = 4;
	Client my_client(my_route, my_FIO, my_voucher_count);
	cout << "Client's FIO: " << my_client.getFIO() << endl;
	cout << "Client's vouchers' amount: " << my_client.getVoucher_Count() << endl << endl;
	cout << "Information about the voucher:" << endl;
	cout << "Voucher's county: " << my_client.getRoute().getCountry() << endl;
	cout << "Voucher's type: " << my_client.getRoute().getVoucher() << endl;
	cout << "Voucher's price (price per ticket): " << my_client.getRoute().getPrice() << endl << endl;
	cout << "The whole cost of the route: " << my_client.Calc_Tickets_Cost() << endl << endl;
	system("pause");
	return 0;
}