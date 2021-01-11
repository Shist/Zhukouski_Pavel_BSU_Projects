#include <iostream>
#include <list>
#include <string>
using namespace std;

#pragma once
class WeatherDate
{ // ����� - "������ �� ����"
private:
	pair<int, double> year_1; // ���� (1-�� ��� � ��� �����������)
	pair<int, double> year_2; // ���� (2-�� ��� � ��� �����������)
	pair<int, double> year_3; // ���� (3-�� ��� � ��� �����������)
	int month; // �����
	int day; // ����
public:
	WeatherDate(int aday, int amonth, int ayear_1, double atemp_1, int ayear_2, double atemp_2, int ayear_3, double atemp_3)
	{ // ����������� ������� ������
		if (amonth < 1 || amonth > 12)
			throw exception("������������ �������� ������!");
		if (aday < 1 || aday > 31)
			throw exception("������������ �������� ���!");
		if (amonth == 2 && aday > 29)
			throw exception("������������ �������� ��� ��� �������!");
		month = amonth;
		day = aday;
		year_1 = make_pair(ayear_1, atemp_1);
		year_2 = make_pair(ayear_2, atemp_2);
		year_3 = make_pair(ayear_3, atemp_3);
	}

	virtual ~WeatherDate() {} // ����������� ���������� (�����, ����� ������� ������� ������ ��� ������ �� ������������ ���)

	int GetYear_1() const
	{ // ������ ��� 1-�� ����
		return year_1.first;
	}

	double GetTemp_1() const
	{ // ������ ��� 1-�� �����������
		return year_1.second;
	}

	int GetYear_2() const
	{ // ������ ��� 2-�� ����
		return year_2.first;
	}

	double GetTemp_2() const
	{ // ������ ��� 2-�� �����������
		return year_2.second;
	}

	int GetYear_3() const
	{ // ������ ��� 3-��� ����
		return year_3.first;
	}

	double GetTemp_3() const
	{ // ������ ��� 3-�� �����������
		return year_3.second;
	}

	int GetMonth() const
	{ // ������ ��� ������
		return month;
	}

	int GetDay() const
	{ // ������ ��� ���
		return day;
	}

	virtual double AverageYearTemp() const
	{ // �������, ������������ ������� �������� ����������� �� ��� ����
		double result = 0.0;
		result += GetTemp_1();
		result += GetTemp_2();
		result += GetTemp_3();
		result /= 3;
		return result;
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	list<WeatherDate*> WeatherDateList; // ������� ���� �� 5 �������� ������
	WeatherDate *WD_1 = new WeatherDate(12, 7, 2017, 24.3, 2018, 30.5, 2018, 27.8);
	WeatherDateList.push_back(WD_1);
	WeatherDate *WD_2 = new WeatherDate(13, 7, 2017, 22.5, 2018, 29.5, 2018, 32.7);
	WeatherDateList.push_back(WD_2);
	WeatherDate *WD_3 = new WeatherDate(14, 7, 2017, 21.0, 2018, 31.5, 2018, 31.5);
	WeatherDateList.push_back(WD_3);
	WeatherDate *WD_4 = new WeatherDate(15, 7, 2017, 28.6, 2018, 34.5, 2018, 29.9);
	WeatherDateList.push_back(WD_4);
	WeatherDate *WD_5 = new WeatherDate(16, 7, 2017, 25.6, 2018, 34.9, 2018, 32.4);
	WeatherDateList.push_back(WD_5);
	int count = 1;
	for (list<WeatherDate*>::iterator it = WeatherDateList.begin(); it != WeatherDateList.end(); it++)
	{
		cout << "���������� � " << count << " �������:" << endl;
		cout << "����: " << (*(*it)).GetDay() << "." << (*(*it)).GetMonth() << "." << (*(*it)).GetYear_1()
			<< ", ����������� ����������: " << (*(*it)).GetTemp_1() << " ��������." << endl;
		cout << "����: " << (*(*it)).GetDay() << "." << (*(*it)).GetMonth() << "." << (*(*it)).GetYear_2()
			<< ", ����������� ����������: " << (*(*it)).GetTemp_2() << " ��������." << endl;
		cout << "����: " << (*(*it)).GetDay() << "." << (*(*it)).GetMonth() << "." << (*(*it)).GetYear_3()
			<< ", ����������� ����������: " << (*(*it)).GetTemp_3() << " ��������." << endl;
		cout << "������� ����������� �� ��� ��� ���� ����������: " << (*(*it)).AverageYearTemp() << endl << endl;
		count++;
	}
	return 0;
}