#pragma once
#include <iostream>
#include <exception>
using namespace std;

class VolumeSystem
{
private:
	const double liters_in_chrk = 0.123; // Количество литров в одной чарке
	int shtof; // Штофы
	int bottl; // Бутылки
	double chrk; // Чарки
	VolumeSystem(); // Конструктор по умолчанию (на всякий случай пусть будет)
	void VolumeReduction(); // Функция, которая будет упрощать значение объёма, если это возможно
public:
	VolumeSystem(long long, long long, long double); // Конструктор
	virtual ~VolumeSystem(); // Виртуальный деструктор
	int Get_Shtof() const; // Геттер для штоф
	int Get_Bottl() const; // Геттер для бутылок
	double Get_Chrk() const; // Геттер для чарок
	void Set_Shtof(long long); // Сеттер для штоф
	void Set_Bottl(long long); // Сеттер для бутылок
	void Set_Chrk(long double); // Сеттер для чарок
	bool operator == (const VolumeSystem&) const; // Равенство
	bool operator != (const VolumeSystem&) const; // Неравенство
	bool operator < (const VolumeSystem&) const; // Меньше
	bool operator <= (const VolumeSystem&) const; // Меньше либо равно
	bool operator > (const VolumeSystem&) const; // Больше
	bool operator >= (const VolumeSystem&) const; // Больше либо равно
	friend ostream& operator << (ostream&, const VolumeSystem&); // Функция для форматированного вывода значения объёма
	VolumeSystem operator + (const VolumeSystem&) const; // Сложение
	VolumeSystem operator - (const VolumeSystem&) const; // Вычитание
	VolumeSystem& operator += (const VolumeSystem&); // Сложение с присвоением
	VolumeSystem& operator -= (const VolumeSystem&); // Вычитание с присвоением
	double GetVolume(); // Получить информацию об объёме объекта
};