#include "pch.h"
#include <iostream>
#include "Mum_Dad.h"
#include <string>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string tName;
	int key = 0;
	cout << "Введите \"1\", если вы хотите сделать ручной ввод данных для тредов, или \"2\", если хотите автоматический: ";
	cin >> key;
	if (key == 1)
	{
		int rAmount;
		int tTime;
		int x;
		cout << "В данной программе вам предложено поработать с четырьмя тредами!" << endl;
		cout << "Введите желаемое максимальное количество повторений для всех тредов: ";
		cin >> x;
		if (x <= 0)
		{
			cout << "Введено некорректное количество повторений для всех тредов" << endl;
			return -2;
		}
		Mum_Dad::Whole_Count = x;
		cout << "Максимальное количество повторений равно " << Mum_Dad::Whole_Count << endl;
		cout << "Введите название первого треда: ";
		cin >> tName;
		cout << "Введите количество повторений для первого треда: ";
		cin >> rAmount;
		if (rAmount <= 0)
		{
			cout << "Введено некорректное количество повторений для первого треда" << endl;
			return -3;
		}
		cout << "Введите время между повторениями в первом треде: ";
		cin >> tTime;
		if (tTime <= 0)
		{
			cout << "Введено некорректное время между повторениями для первого треда" << endl;
			return -4;
		}
		Mum_Dad mt(tName, rAmount, tTime);
		tName.clear();
		cout << "Введите название второго треда: ";
		cin >> tName;
		cout << "Введите количество повторений для второго треда: ";
		cin >> rAmount;
		if (rAmount <= 0)
		{
			cout << "Введено некорректное количество повторений для второго треда" << endl;
			return -5;
		}
		cout << "Введите время между повторениями во втором треде: ";
		cin >> tTime;
		if (tTime <= 0)
		{
			cout << "Введено некорректное время между повторениями для второго треда" << endl;
			return -6;
		}
		Mum_Dad mt2(tName, rAmount, tTime);
		tName.clear();
		cout << "Введите название третьего треда: ";
		cin >> tName;
		cout << "Введите количество повторений для третьего треда: ";
		cin >> rAmount;
		if (rAmount <= 0)
		{
			cout << "Введено некорректное количество повторений для третьего треда" << endl;
			return -7;
		}
		cout << "Введите время между повторениями в третьем треде: ";
		cin >> tTime;
		if (tTime <= 0)
		{
			cout << "Введено некорректное время между повторениями для третьего треда" << endl;
			return -8;
		}
		Mum_Dad mt3(tName, rAmount, tTime);
		tName.clear();
		cout << "Введите название четвертого треда: ";
		cin >> tName;
		cout << "Введите количество повторений для четвертого треда: ";
		cin >> rAmount;
		if (rAmount <= 0)
		{
			cout << "Введено некорректное количество повторений для четвертого треда" << endl;
			return -9;
		}
		cout << "Введите время между повторениями в четвертом треде: ";
		cin >> tTime;
		if (tTime <= 0)
		{
			cout << "Введено некорректное время между повторениями для четвертого треда" << endl;
			return -10;
		}
		Mum_Dad mt4(tName, rAmount, tTime);
		thread* newThrd = new thread(&Mum_Dad::Run, mt);
		thread* newThrd2 = new thread(&Mum_Dad::Run, mt2);
		thread* newThrd3 = new thread(&Mum_Dad::Run, mt3);
		thread* newThrd4 = new thread(&Mum_Dad::Run, mt4);
		newThrd->join();
		newThrd2->join();
		newThrd3->join();
		newThrd4->join();
		delete newThrd;
		delete newThrd2;
		delete newThrd3;
		delete newThrd4;
	}
	else if (key == 2)
	{
		Mum_Dad::Whole_Count = 15;
		Mum_Dad mt("Первый_тред", 10, 100);
		Mum_Dad mt2("Второй_тред", 10, 500);
		Mum_Dad mt3("Третий_тред", 10, 1000);
		Mum_Dad mt4("Четвертый_тред", 10, 1500);
		thread* newThrd = new thread(&Mum_Dad::Run, mt);
		thread* newThrd2 = new thread(&Mum_Dad::Run, mt2);
		thread* newThrd3 = new thread(&Mum_Dad::Run, mt3);
		thread* newThrd4 = new thread(&Mum_Dad::Run, mt4);
		newThrd->join();
		newThrd2->join();
		newThrd3->join();
		newThrd4->join();
		delete newThrd;
		delete newThrd2;
		delete newThrd3;
		delete newThrd4;
	}
	else
	{
		cout << "Введено некорректное значение ключа!" << endl;
		return  -1;
	}
	return 0;
}