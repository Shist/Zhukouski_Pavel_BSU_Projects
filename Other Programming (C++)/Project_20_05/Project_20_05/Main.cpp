#include <iostream>
#include <string>
using namespace std;

struct Provider
{
	string Number; // номер абонента
	int TrafficLimit; // лимит трафика (ГБ)
	int Payment; // абонентская плата ($)
	Provider(string number = string("0"), int trafficLimit = 0, int payment = 0) // конструктор
		: Number(number), TrafficLimit(trafficLimit), Payment(payment)
	{}
};

void PrintAllProviders(Provider *providers, int kol)
{
	for (int i = 0; i < kol; ++i)
		cout << "Number: " << providers[i].Number
			 << "\nLimit: " << providers[i].TrafficLimit << " GB"
			 << "\nPayment: " << providers[i].Payment << " $\n\n";
}

void FindAndPrintSum(Provider *providers, int kol, string number, int usedTraffic)
{
	for (int i = 0; i < kol; ++i)
		if (providers[i].Number == number)
		{
			double sumToPay =
				(usedTraffic <= providers[i].TrafficLimit
					? providers[i].Payment
					: providers[i].Payment * 1.1);
			cout << "The subscriber " << number << " has to pay " << sumToPay << " $\n";
			return;
		}
	cout << "Don't have a subscriber " << number << "!\n";
}

int main()
{
	int N = 5;
	Provider *providers = new Provider[N];
	providers[0] = Provider("523-45-61", 2, 10);
	providers[1] = Provider("262-34-24", 4, 20);
	providers[2] = Provider("863-48-47", 8, 30);
	providers[3] = Provider("113-97-62", 16, 40);
	providers[4] = Provider("474-42-47", 32, 50);
	PrintAllProviders(providers, N);

	string number = "863-48-47";
	int usedTraffic = 10;
	FindAndPrintSum(providers, N, number, usedTraffic);

	delete[] providers;
	system("pause");
	return 0;
}