#pragma once // Предотвращаем ошибки, связанные с повторным описанием класса
#include <iostream>
#include <exception>
using namespace std;

class Money
{
private:
	long long sum; // В этой переменной будем хранить число, равное pd * sh * 2 * p
	bool check = false; // Вводим флажок, который будет указывать set-методу, как ему расчитывать sum
public:
	Money(); // Конструктор без параметров (задает нулевую сумму)
	Money(int, int, double); // Конструктор с тремя параметрами, который хранит 3 переменных (денежные валюты)
	virtual ~Money(); // Виртуальный деструктор
	long long get_sum() const; // Для получения информации о сумме
	void set_sum(int, int, double, long long); // Для изменения информации о сумме
	Money operator + (const Money&) const; // Сложение
	Money operator - (const Money&) const; // Вычитание
	Money operator - () const; // Унарный минус
	Money operator += (const Money& x); // Сложение с присвоением
	Money operator -= (const Money& x); // Вычитание с присвоением
	bool operator == (const Money&) const; // Сравнение (равно)
	friend ostream& operator << (ostream& s, const Money& x);
};