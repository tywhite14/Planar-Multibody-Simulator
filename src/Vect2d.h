#pragma once


struct Vect2d
{
	double x, y;

	Vect2d();
	Vect2d(double a, double b);
	Vect2d(double b);

	Vect2d operator+(const Vect2d& b) const {
		return { x + b.x, y + b.y };
	}
	Vect2d operator-(const Vect2d& b) const {
		return { x - b.x, y - b.y };
	}
	Vect2d operator-() const {
		return { -x, -y };
	}
	Vect2d operator*(double s) const {
		return { x * s, y * s };
	}
	Vect2d operator/(double s) const {
		return Vect2d(x / s, y / s);
	}
	bool operator==(Vect2d& b) const {
		if ((x == b.x) && (y == b.y))
			return true;
		else
			return false;
	}
};

