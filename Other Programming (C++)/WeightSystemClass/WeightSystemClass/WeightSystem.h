#pragma once
#include <iostream>
#include <exception>
using namespace std;

class WeightSystem
{
private:
	const double kilo_in_zol = 0.004265625; // Количество килограмм в одном золотнике
	int pud; // Пуды
	int fut; // Фунты
	int zol; // Золотники
	WeightSystem(); // Конструктор по умолчанию (на всякий случай пусть будет)
	void WeightReduction(); // Функция, которая будет упрощать значение веса, если это возможно
public:
	WeightSystem(long long, long long, long long); // Конструктор
	virtual ~WeightSystem(); // Виртуальный деструктор
	int Get_Pud() const; // Геттер для пудов
	int Get_Fut() const; // Геттер для фунтов
    int Get_Zol() const; // Геттер для золотников
	void Set_Pud(long long); // Сеттер для пудов
	void Set_Fut(long long); // Сеттер для фунтов
	void Set_Zol(long long); // Сеттер для золотников
	bool operator == (const WeightSystem&) const; // Равенство
	bool operator != (const WeightSystem&) const; // Неравенство
	bool operator < (const WeightSystem&) const; // Меньше
	bool operator <= (const WeightSystem&) const; // Меньше либо равно
	bool operator > (const WeightSystem&) const; // Больше
	bool operator >= (const WeightSystem&) const; // Больше либо равно
	friend ostream& operator << (ostream&, const WeightSystem&); // Функция для форматированного вывода значения веса
	WeightSystem operator + (const WeightSystem&) const; // Сложение
	WeightSystem operator - (const WeightSystem&) const; // Вычитание
	WeightSystem& operator += (const WeightSystem&); // Сложение с присвоением
	WeightSystem& operator -= (const WeightSystem&); // Вычитание с присвоением
	double GetWeight(); // Получить информацию о весе объекта
};