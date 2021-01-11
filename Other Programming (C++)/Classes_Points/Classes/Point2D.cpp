#include "Point2D.h"

Point2D::Point2D(double ax, double ay)
{
	setx(ax);
	sety(ay);
}


Point2D::~Point2D()
{
}

double Point2D::getx() const
{
	return x;
}

void Point2D::setx(double ax)
{
	x = ax;
}

double Point2D::gety() const
{
	return y;
}

void Point2D::sety(double ay)
{
	y = ay;
}

double Point2D::getRo() const
{
	return sqrt(x * x + y * y);
}

double Point2D::getPhi() const
{
	if (x == 0 && y == 0)
		throw exception("Impossible to calculate Phi for point (0, 0)");
	if (x > 0 && y == 0)
		return 0;
	if (x < 0 && y == 0)
		return PI;
	if (x == 0 && y > 0)
		return PI / 2;
	if (x == 0 && y < 0)
		return -PI / 2;
	if ((x > 0 && y > 0) || (x > 0 && y < 0))
		return atan(y / x);
	if ((x > 0 && y < 0) || (x < 0 && y > 0))
		return atan(y / x) + PI;
}

Point2D Point2D::operator - () const
{
	return Point2D(-x, -y); // унарный минус
}

Point2D& Point2D::operator ++ () // инкремент (префиксный)
{
	x++;
	y++;
	return *this;
}

Point2D Point2D::operator ++ (int a) // инкремент (постфиксный)
{
	Point2D p(*this);
	x++;
	y++;
	return p;
}

Point2D Point2D::operator + (const Point2D& p) const
{
	return Point2D(x + p.x, y + p.y); // сложение
}

double Point2D::operator * (const Point2D& p) const
{
	return (x*p.x + y * p.y); // скалярное произведение
}

bool Point2D::operator == (const Point2D& p) const
{
	return (x == p.x && y == p.y); // Сравнение (равно)
}

bool Point2D::operator != (const Point2D& p) const
{
	return (! this->operator==(p)); // Сравнение (не равно)
}

Point2D Point2D::operator * (double d) const
{
	return Point2D(d*x, d*y); // Умножение на число
}

Point2D operator * (double d, const Point2D& p)
{
	return p.operator * (d); // Умножение на число (это для реализации коммутативности)
}

ostream& operator << (ostream& s, const Point2D& p)
{
	s << "(" << p.x << ", " << p.y << ")"; // РЕАЛИЗАЦИЯ ВЫВОДА В ПОТОК!!! ОЧЕНЬ ВАЖНАЯ ВЕЩЬ ДЛЯ ЛЮБОГО КЛАССА!!!
	return s;
}

string Point2D::toString() const
{
	ostringstream str;
	str << "(" << x << ", " << y << ")";
	return str.str();
}

Point2D::operator double()
{
	return getRo();
}