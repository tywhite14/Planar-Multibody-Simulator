#pragma once

#include <iostream>
#include <initializer_list>
#include <cmath>

class Vec2d
{
public:
	Vec2d();
	Vec2d(const double s);
	Vec2d(const double xi, const double yi);

	// members
	inline double magnitude() const { return std::sqrt(x*x + y*y); }
	inline Vec2d zeros() const { return Vec2d(0.0); };
	inline Vec2d ones()  const { return Vec2d(1.0); };
	Vec2d random() const;
	Vec2d randi(const int max, bool pm = true) const;
	inline Vec2d rotate(const double angle) const { return Vec2d(std::cos(angle) * x - std::sin(angle) * y, std::sin(angle) * x + std::cos(angle) * y); }
	inline Vec2d rot90() const { return Vec2d(-y, x); }

	// operator overloading
	inline Vec2d operator-() const { return Vec2d(-x, -y); }
	inline Vec2d operator+(const Vec2d& b) const { return Vec2d(x + b.x, y + b.y); }
	inline Vec2d operator-(const Vec2d& b) const { return Vec2d(x - b.x, y - b.y); }
	inline Vec2d operator%(const Vec2d& b) const { return Vec2d(x * b.x, y * b.y); }
	inline Vec2d operator*(const double s) const { return Vec2d(x * s, y * s); }
	inline bool operator==(const Vec2d& b) const { return (x == b.x && y == b.y); }
	Vec2d operator=(const std::initializer_list<double>& list);
	friend std::ostream& operator<<(std::ostream& os, const Vec2d& v);

	double x, y;

private:
};

inline Vec2d operator*(const double s, const Vec2d& v) {
	return Vec2d(s * v.x, s * v.y);
}
