#pragma once

class Tariff
{
public:
	Tariff(); // �����������
	virtual ~Tariff(); // ����������� ����������
	int Year; // ���
	int Month_number; // ����� ������
	int Balance_begin; // ������ �� ������ ������
	char* Tariff_plan; // �������� ���� (��������)
	int Subscription; // ����������� �����
	int Outgoing_velcom; // ��������� �� velcom � 3G
	int Outgoing_mts; // ��������� �� ��� 3G
	int Outgoing_rb; // ��������� �� �� 3G
	int MMS_international; // MMS ��������� �������������
	int MMS_national; // MMS ��������� ������������
	int USSD; // USSD
	int SMS_international; // SMS ��������� �������������
	int SMS_national; // SMS ��������� ������������
	int Balance_end; // ������ �� ����� ������
	int Paid_period; // �������� �� ������
	int Total; // ����� ����������
	int Total_nds; // ����� � ������
	void Total_accruals // ����� ����������
	(int Cost_min_velcom, // ��������� ����� ������ �� velcom
		int Cost_min_mts, // ��������� ����� ������ �� mts
		int Cost_min_rb, // ��������� ����� ������ �� ��
		int Cost_mms_intern, // ��������� ��� �������������
		int Cost_mms_nat, // ��������� ��� ������������
		int Cost_ussd, // ��������� USSD
		int Cost_sms_intern, // ��������� SMS �������������
		int Cost_sms_nat, // ��������� SMS ������������
		int Number_free_minutes); // ���������� ���������� �����
	void Including_tax(int NDS); // ���������� � ���-��� NDS
};