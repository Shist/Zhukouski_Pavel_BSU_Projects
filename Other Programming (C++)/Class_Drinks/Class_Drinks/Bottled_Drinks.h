#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Bottled_Drinks
{
protected:
	string name_drink; // ��� �������
	int tare_volume; // ����� (� ��)
public:
	Bottled_Drinks(); // ����������� (��������)
	virtual ~Bottled_Drinks(); // ����������� ����������
	virtual string get_name() const = 0; // ����������� ������ (��� �������)
	virtual int get_volume() const = 0; // ����������� ������ (����� �������)
};