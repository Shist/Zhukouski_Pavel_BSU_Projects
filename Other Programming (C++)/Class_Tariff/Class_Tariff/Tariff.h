#pragma once

class Tariff
{
public:
	Tariff(); // Конструктор
	virtual ~Tariff(); // Виртуальный деструктор
	int Year; // Год
	int Month_number; // Номер месяца
	int Balance_begin; // Баланс на начало месяца
	char* Tariff_plan; // Тарифный план (название)
	int Subscription; // Абонентская плата
	int Outgoing_velcom; // Исходящие на velcom в 3G
	int Outgoing_mts; // Исходящие на МТС 3G
	int Outgoing_rb; // Исходящие по РБ 3G
	int MMS_international; // MMS исходящие международные
	int MMS_national; // MMS исходящие национальные
	int USSD; // USSD
	int SMS_international; // SMS исходящие международные
	int SMS_national; // SMS исходящие национальные
	int Balance_end; // Баланс на конец месяца
	int Paid_period; // Оплачено за период
	int Total; // Итого начислений
	int Total_nds; // Итого к оплате
	void Total_accruals // Итого начислений
	(int Cost_min_velcom, // Стоимость одной минуты на velcom
		int Cost_min_mts, // Стоимость одной минуты на mts
		int Cost_min_rb, // Стоимость одной минуты по РБ
		int Cost_mms_intern, // Стоимость ММС международной
		int Cost_mms_nat, // Стоимость ММС национальной
		int Cost_ussd, // Стоимость USSD
		int Cost_sms_intern, // Стоимость SMS международной
		int Cost_sms_nat, // Стоимость SMS национальной
		int Number_free_minutes); // Количество бесплатных минут
	void Including_tax(int NDS); // Начисления с учё-том NDS
};