#pragma once
#include "Alcoholic_Drinks.h"

enum class Raw_Mat // виды сырья для пива
{
	Wheat, // пшеница
	Barley, // ячмень
	Ginger // имбирь
};

class Beer :
	public Alcoholic_Drinks // наследуем от класса "Алкогольные напитки"
{
private:
	Raw_Mat mater; // материал, из которого сделано пиво
public:
	Beer(string, int, double, Raw_Mat); // конструктор для пива (название, объем в мл, процент спирта, материал)
	virtual ~Beer(); // виртуальный деструктор
	string get_name() const; // геттер (возвращает название пива)
	int get_volume() const; // геттер (возвращает объем пива)
	double get_alc_perc() const; // геттер (возвращает процент алкоголя в пиве)
	Raw_Mat get_mater() const; // геттер для материала, из которого сделано пиво (его вывести в поток так просто не получится)
	void output_mater(ostream& out) const; // для вывода вида материала в поток
};