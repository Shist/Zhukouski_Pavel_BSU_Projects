#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Bottled_Drinks
{
protected:
	string name_drink; // имя напитка
	int tare_volume; // объем (в мл)
public:
	Bottled_Drinks(); // конструктор (пустышка)
	virtual ~Bottled_Drinks(); // виртуальный деструктор
	virtual string get_name() const = 0; // виртуальный геттер (имя напитка)
	virtual int get_volume() const = 0; // виртуальный геттер (объем напитка)
};