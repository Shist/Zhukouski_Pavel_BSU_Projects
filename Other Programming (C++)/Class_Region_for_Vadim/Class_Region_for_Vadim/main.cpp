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
	Region r1("Ленинский", 3089.56, 570);
	Region r2("Советский", 4756.2, 345);
	Region r3("Партизанский", 3907.89, 675.2);
	Region r4("Фрунзенский", 5098.8, 456.8);
	Region r5("Заводской", 4098.6, 589.3);
	ofstream fout("output.txt"); // В папке появится файлик output.txt со всеми данными
	fout << "Район " << r1.getRegionName() << " имеет следующий показатель обеспеченности жильём населения: " << r1.getPopulation() / r1.getArea() << endl;
	fout << "Район " << r2.getRegionName() << " имеет следующий показатель обеспеченности жильём населения: " << r2.getPopulation() / r2.getArea() << endl;
	fout << "Район " << r3.getRegionName() << " имеет следующий показатель обеспеченности жильём населения: " << r3.getPopulation() / r3.getArea() << endl;
	fout << "Район " << r4.getRegionName() << " имеет следующий показатель обеспеченности жильём населения: " << r4.getPopulation() / r4.getArea() << endl;
	fout << "Район " << r5.getRegionName() << " имеет следующий показатель обеспеченности жильём населения: " << r5.getPopulation() / r5.getArea() << endl;
	fout.close();
	return 0;
}