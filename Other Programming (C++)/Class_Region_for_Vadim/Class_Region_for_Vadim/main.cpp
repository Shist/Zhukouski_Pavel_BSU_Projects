#include <fstream>
#include <string>
using namespace std;

#pragma once

class Region
{
private:
	string regionName;
	double area;
	double population;
public:
	Region(string aRegionName, double anArea, double aPopulation)
		: regionName(aRegionName), area(anArea), population(aPopulation) {}
	virtual ~Region() {}

	string getRegionName() const
	{
		return regionName;
	}

	double getArea() const
	{
		return area;
	}

	double getPopulation() const
	{
		return population;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Region r1("���������", 3089.56, 570);
	Region r2("���������", 4756.2, 345);
	Region r3("������������", 3907.89, 675.2);
	Region r4("�����������", 5098.8, 456.8);
	Region r5("���������", 4098.6, 589.3);
	ofstream fout("output.txt"); // � ����� �������� ������ output.txt �� ����� �������
	fout << "����� " << r1.getRegionName() << " ����� ��������� ���������� �������������� ������ ���������: " << r1.getPopulation() / r1.getArea() << endl;
	fout << "����� " << r2.getRegionName() << " ����� ��������� ���������� �������������� ������ ���������: " << r2.getPopulation() / r2.getArea() << endl;
	fout << "����� " << r3.getRegionName() << " ����� ��������� ���������� �������������� ������ ���������: " << r3.getPopulation() / r3.getArea() << endl;
	fout << "����� " << r4.getRegionName() << " ����� ��������� ���������� �������������� ������ ���������: " << r4.getPopulation() / r4.getArea() << endl;
	fout << "����� " << r5.getRegionName() << " ����� ��������� ���������� �������������� ������ ���������: " << r5.getPopulation() / r5.getArea() << endl;
	fout.close();
	return 0;
}