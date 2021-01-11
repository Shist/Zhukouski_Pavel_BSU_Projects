#include "Tariff.h"



Tariff::Tariff() // Конструктор
{
	Year = 0; // Год
	Month_number = 0; // Номер месяца
	Balance_begin = 0; // Баланс на начало месяца
	Tariff_plan = nullptr; // Тарифный план (название)
	Subscription = 0; // Абонентская плата
	Outgoing_velcom = 0; // Исходящие на velcom в 3G
	Outgoing_mts = 0; // Исходящие на МТС 3G
	Outgoing_rb = 0; // Исходящие по РБ 3G
	MMS_international = 0; // MMS исходящие международные
	MMS_national = 0; // MMS исходящие национальные
	USSD = 0; // USSD
	SMS_international = 0; // SMS исходящие международные
	SMS_national = 0; // SMS исходящие национальные
	Balance_end = 0; // Баланс на конец месяца
	Paid_period = 0; // Оплачено за период
	Total = 0; // Итого начислений
	Total_nds = 0; // Итого к оплате
}


Tariff::~Tariff() // Виртуальный деструктор
{
}

void Tariff::Total_accruals // Итого начислений
(int Cost_min_velcom, // Стоимость одной минуты на velcom
	int Cost_min_mts, // Стоимость одной минуты на mts
	int Cost_min_rb, // Стоимость одной минуты по РБ
	int Cost_mms_intern, // Стоимость ММС международной
	int Cost_mms_nat, // Стоимость ММС национальной
	int Cost_ussd, // Стоимость USSD
	int Cost_sms_intern, // Стоимость SMS международной
	int Cost_sms_nat, // Стоимость SMS национальной
	int Number_free_minutes)
{ // TODO
	Total /* = F(Cost_min_mts, Cost_min_rb, Cost_mms_intern, Cost_mms_nat, Cost_ussd, Cost_sms_intern, Cost_sms_nat, Number_free_minutes) */ ;
}

void Tariff::Including_tax(int NDS) // Начисления с учё-том NDS
{ // TODO
	Total_nds /* = F(NDS) */ ;
}