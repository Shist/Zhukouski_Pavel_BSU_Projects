#pragma once
#include "Route.h"
#include <string>
using namespace std;

class Client
{
private:
	Route route; // Маршрут
	string FIO; // ФИО клиента
	unsigned int voucher_count; // Количество путёвок
public:
	Client(Route aRoute, string aFIO, unsigned int aVoucher_Count); // Конструктор
	Client(); // Конструктор по умолчанию
	virtual ~Client(); // Виртуальный деструктор
	Route getRoute() const; // Геттер для маршрута
	string getFIO() const; // Геттер для ФИО
	unsigned int getVoucher_Count() const; // Геттер для количества путёвок
	double Calc_Tickets_Cost(); // Функция для расчёта стоимости путёвок
};