#include <iostream>
#include "Point3D.h"
using namespace std;

void PrintPoint(const Point2D& p) {
	cout << p.getx() << " " << p.gety();
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int x, y;
	cout << "¬ведите координаты точки (сначала x, потом y), с которой хотите работать: " << endl;
	cin >> x;
	cin >> y;
	Point2D p0(x, y);
	Point2D p1(1, 3);
	cout << " оординаты заданной точки следующие: ";
	cout << p0 << endl; // вывод
	//cout << p0.toString() << endl; альтернатива выводу
	if (p0 == p1)
	{
		cout << "«аданна€ точка совпадает с точкой p1" << endl;
	}
	else
	{
		cout << "«аданна€ точка не совпадает с точкой p1" << endl;
	}
	// cout << 3*p; так будет ошибка C2666 
	cout << operator*(3, p0) << endl; // Ќаходим новые координаты точек, если был перевод типа 
	cout << 3 * (double)p0 << endl; // считаем рассто€ние от начала координат
	try
	{
		//cout << p.getPhi();
		//cout << p.getRo();
	}
	catch (exception err)
	{
		//cout << err.what();
	}
	return 0;
}