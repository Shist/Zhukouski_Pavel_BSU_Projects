#pragma once
#include "Alcoholic_Drinks.h"

enum class Excerpt
{ // Виды коньяка
	deLuxe,
	Superior,
	Vieux,
	GrandReserve
};

class Cognac :
	public Alcoholic_Drinks // наследуем от класса "Алкогольные напитки"
{
private:
	Excerpt exc;
public:
	Cognac(string, int, double, Excerpt); // конструктор для коньяка (название, объем в мл, процент спирта, вид)
	virtual ~Cognac(); // виртуальный деструктор
	string get_name() const; // геттер (возвращает название коньяка)
	int get_volume() const; // геттер (возвращает объем коньяка)
	double get_alc_perc() const; // геттер (возвращает процент алкоголя в коньяке)
	Excerpt get_exc() const; // геттер (возвращает вид коньяка)
};