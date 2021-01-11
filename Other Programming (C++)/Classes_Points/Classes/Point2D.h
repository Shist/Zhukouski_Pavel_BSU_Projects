#pragma once
#include <exception>
#include <cmath>
#include <iostream>
#include <sstream>
#define PI 3.143159265358
using namespace std;

class Point2D
{
private: // �� ������ � �� ����, � �������� �������� ������ ��������� ������
	double x, y;
public: // �� ������ � �� ����, � ������� ����� ���������� ������������ ������
	Point2D(double = 0, double = 0);
	virtual ~Point2D();
	double getx() const;
	void setx(double);
	double gety() const;
	void sety(double);
	double getRo() const;
	double getPhi() const;
	Point2D operator - () const; // ������� �����
	Point2D& operator ++ (); // ���������(����������)
	Point2D operator ++ (int); // ���������(�����������)
	Point2D operator + (const Point2D&) const; // ��������
	double operator * (const Point2D&) const;
	bool operator == (const Point2D&) const; // �������� (�����)
	bool operator != (const Point2D&) const; // �������� (�� �����)
	Point2D operator * (double) const; // ��������� �� �����
	friend Point2D operator * (double, const Point2D&); // ��������� �� ����� (��� ��� ���������� ���������������)
	friend ostream& operator << (ostream&, const Point2D&); // ���������� ������ � �����!!!
	string toString() const; // ������������ ������ � �����
	operator double();
	virtual double Module();
};
// �������� ��� ������� Point2D
// 1) �������� � ��������� ����� (�� �������� �������� � ��������� ��������);
// 2) ������� ����� (�� �������� ��������);
// 3) ��������� ����� �� ����� � ����� �� ����� (��������� - ���������� ��� ������ �����);
// 4) ��������� ���� �����(��������� � ��������� ������������);
// 5) ��������� � ��������� �����(��������� � ���������� ��� ���������� ��������� �� 1);
// 6) ��������� �� ��������� � ����������� ���� �����.)