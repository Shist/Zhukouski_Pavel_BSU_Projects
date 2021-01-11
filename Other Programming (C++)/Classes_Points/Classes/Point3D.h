#pragma once
#include "Point2D.h"


class Point3D : public Point2D {
private:
	double z;
public:
	Point3D(double = 0, double = 0, double = 0);
	virtual ~Point3D();
	double getz() const;
	void setz(double az);
	virtual double Module() const;
};