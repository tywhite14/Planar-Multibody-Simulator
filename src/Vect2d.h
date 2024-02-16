#pragma once

#include <iostream>

class Vect2d
{
public:
	double x, y;

	Vect2d();
	Vect2d(double a, double b);
	Vect2d(double b);

	Vect2d operator+(const Vect2d& b) const;
	Vect2d operator-(const Vect2d& b) const;
	Vect2d operator-() const;
	Vect2d operator*(double s) const;
	Vect2d operator/(double s) const;
	bool   operator==(Vect2d& b) const;

	Vect2d rotate(const double angle) const;
	Vect2d rotate90() const;
	friend std::ostream& operator<<(std::ostream& os, const Vect2d& vec);
};
