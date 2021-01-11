#pragma once
#include <string>
using namespace std;

enum voucher_type { treatment, rest, excursion };

class Route
{
private:
	string country; // ������
	voucher_type* voucher; // ������ (��������� �� � ��������)
	double price; // ����
	string voucher_type_value[3] = { "treatment", "rest", "excursion" };
public:
	Route(string aCountry, voucher_type* aVoucher, double aPrice); // �����������
	Route(); // ����������� �� ���������
	virtual ~Route(); // ����������� ����������
	string getCountry() const; // ������ ��� ������
	string getVoucher() const; // ������ ��� ������
	double getPrice() const; // ������ ��� ����
};