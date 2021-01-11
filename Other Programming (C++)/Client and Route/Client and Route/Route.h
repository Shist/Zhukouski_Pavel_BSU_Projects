#pragma once
#include <string>
using namespace std;

enum voucher_type { treatment, rest, excursion };

class Route
{
private:
	string country; // Страна
	voucher_type* voucher; // Путёвка (указатель на её значение)
	double price; // Цена
	string voucher_type_value[3] = { "treatment", "rest", "excursion" };
public:
	Route(string aCountry, voucher_type* aVoucher, double aPrice); // Конструктор
	Route(); // Конструктор по умолчанию
	virtual ~Route(); // Виртуальный деструктор
	string getCountry() const; // Геттер для страны
	string getVoucher() const; // Геттер для путёвки
	double getPrice() const; // Геттер для цены
};