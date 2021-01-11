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
	cout << "������� ���������� ����� (������� x, ����� y), � ������� ������ ��������: " << endl;
	cin >> x;
	cin >> y;
	Point2D p0(x, y);
	Point2D p1(1, 3);
	cout << "���������� �������� ����� ���������: ";
	cout << p0 << endl; // �����
	//cout << p0.toString() << endl; ������������ ������
	if (p0 == p1)
	{
		cout << "�������� ����� ��������� � ������ p1" << endl;
	}
	else
	{
		cout << "�������� ����� �� ��������� � ������ p1" << endl;
	}
	// cout << 3*p; ��� ����� ������ C2666 
	cout << operator*(3, p0) << endl; // ������� ����� ���������� �����, ���� ��� ������� ���� 
	cout << 3 * (double)p0 << endl; // ������� ���������� �� ������ ���������
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