#include "Tariff.h"



Tariff::Tariff() // �����������
{
	Year = 0; // ���
	Month_number = 0; // ����� ������
	Balance_begin = 0; // ������ �� ������ ������
	Tariff_plan = nullptr; // �������� ���� (��������)
	Subscription = 0; // ����������� �����
	Outgoing_velcom = 0; // ��������� �� velcom � 3G
	Outgoing_mts = 0; // ��������� �� ��� 3G
	Outgoing_rb = 0; // ��������� �� �� 3G
	MMS_international = 0; // MMS ��������� �������������
	MMS_national = 0; // MMS ��������� ������������
	USSD = 0; // USSD
	SMS_international = 0; // SMS ��������� �������������
	SMS_national = 0; // SMS ��������� ������������
	Balance_end = 0; // ������ �� ����� ������
	Paid_period = 0; // �������� �� ������
	Total = 0; // ����� ����������
	Total_nds = 0; // ����� � ������
}


Tariff::~Tariff() // ����������� ����������
{
}

void Tariff::Total_accruals // ����� ����������
(int Cost_min_velcom, // ��������� ����� ������ �� velcom
	int Cost_min_mts, // ��������� ����� ������ �� mts
	int Cost_min_rb, // ��������� ����� ������ �� ��
	int Cost_mms_intern, // ��������� ��� �������������
	int Cost_mms_nat, // ��������� ��� ������������
	int Cost_ussd, // ��������� USSD
	int Cost_sms_intern, // ��������� SMS �������������
	int Cost_sms_nat, // ��������� SMS ������������
	int Number_free_minutes)
{ // TODO
	Total /* = F(Cost_min_mts, Cost_min_rb, Cost_mms_intern, Cost_mms_nat, Cost_ussd, Cost_sms_intern, Cost_sms_nat, Number_free_minutes) */ ;
}

void Tariff::Including_tax(int NDS) // ���������� � ���-��� NDS
{ // TODO
	Total_nds /* = F(NDS) */ ;
}