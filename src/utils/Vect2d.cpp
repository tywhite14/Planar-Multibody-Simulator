#include <cassert>
#include <cmath>
#include <iomanip>

#include "Vect2d.h"
#include "Matrix.h"

class Matrix;

Vect2d::Vect2d() : x(0.0f), y(0.0f) { }
Vect2d::Vect2d(double b) : x(b), y(b) { }
Vect2d::Vect2d(double a, double b) : x(a), y(b) { }

Vect2d Vect2d::operator+(const Vect2d& b) const {
	return { x + b.x, y + b.y };
}

Vect2d Vect2d::operator-(const Vect2d& b) const {
	return { x - b.x, y - b.y };
}

Vect2d Vect2d::operator-() const {
	return { -x, -y };
}

Vect2d Vect2d::operator*(double s) const {
	return { x * s, y * s };
}

Vect2d Vect2d::operator/(double s) const {
	return Vect2d(x / s, y / s);
}

bool Vect2d::operator==(Vect2d& b) const {
	if ((x == b.x) && (y == b.y))
		return true;
	else
		return false;
}

Vect2d Vect2d::rotate(const double angle) const
{
	return Matrix(2, 2) * *this;
}

Vect2d Vect2d::rotate90() const
{
	return Vect2d(-y, x);
}

double Vect2d::mag()
{
	return sqrt(x * x + y * y);
}

double Vect2d::angle()
{
	return atan2(y, x);
}

Vect2d Vect2d::unit()
{
	return *this / mag();
}

std::ostream& operator<<(std::ostream& os, const Vect2d& vec)
{
	os  << "\n" 
		<< std::setw(6) 
		<< std::setprecision(4) 
		<< vec.x << ", " << vec.y 
		<< "\n";

	return os;
}