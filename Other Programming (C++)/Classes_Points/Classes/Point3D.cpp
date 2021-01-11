#include "Point3D.h"



Point3D::Point3D(double ax, double ay, double az)
{
	setx(ax);
	sety(ay);
	setz(az);
}


Point3D::~Point3D()
{
}


double Point3D::getz() const
{
	return z;
}

void Point3D::setz(double az)
{
	z = az;
}


double Point3D::Module() const
{
	double x = getx(), y = gety();
	return sqrt(x*x + y * y + z * z);
}