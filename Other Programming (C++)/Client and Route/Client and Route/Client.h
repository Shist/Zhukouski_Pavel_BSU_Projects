#pragma once
#include "Route.h"
#include <string>
using namespace std;

class Client
{
private:
	Route route; // �������
	string FIO; // ��� �������
	unsigned int voucher_count; // ���������� ������
public:
	Client(Route aRoute, string aFIO, unsigned int aVoucher_Count); // �����������
	Client(); // ����������� �� ���������
	virtual ~Client(); // ����������� ����������
	Route getRoute() const; // ������ ��� ��������
	string getFIO() const; // ������ ��� ���
	unsigned int getVoucher_Count() const; // ������ ��� ���������� ������
	double Calc_Tickets_Cost(); // ������� ��� ������� ��������� ������
};