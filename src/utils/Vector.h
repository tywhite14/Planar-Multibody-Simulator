#pragma once

#include <iostream>
#include <initializer_list>
#include <cmath>

class Vec2d
{
public:
	Vec2d(const double s = 0.0);
	Vec2d(const double xi, const double yi);

	// members
	inline double magnitude() const { return std::sqrt(x * x + y * y); }
	Vec2d random() const;
	Vec2d randi(const int max, bool pm = true) const;
	inline Vec2d rot90() const { return Vec2d(-y, x); }
	inline Vec2d rotate(const double angle) const { 
		return Vec2d(std::cos(angle) * x - std::sin(angle) * y, std::sin(angle) * x + std::cos(angle) * y);
	}

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

class Vec3d
{
public:
	Vec3d(const double s = 0);
	Vec3d(const double xi, const double yi, const double zi);

	// members
	inline double magnitude() const { return std::sqrt(x*x + y*y + z*z); }
	Vec3d random() const;
	Vec3d randi(const int max, bool pm = true) const;

	// operator overloading
	inline Vec3d operator-() const { return Vec3d(-x, -y, -z); }
	inline Vec3d operator+(const Vec3d& b) const { return Vec3d(x + b.x, y + b.y, z + b.z); }
	inline Vec3d operator-(const Vec3d& b) const { return Vec3d(x - b.x, y - b.y, z - b.z); }
	inline Vec3d operator%(const Vec3d& b) const { return Vec3d(x * b.x, y * b.y, z * b.z); }
	inline Vec3d operator*(const double s) const { return Vec3d(x * s, y * s, z * s); }
	inline bool operator==(const Vec3d& b) const { return (x == b.x && y == b.y && z == b.z); }
	Vec3d operator=(const std::initializer_list<double>& list);
	friend std::ostream& operator<<(std::ostream& os, const Vec3d& v);

	double x, y, z;

private:
};

inline Vec2d operator*(const double s, const Vec2d& v) { return v * s; }
inline Vec3d operator*(const double s, const Vec3d& v) { return v * s; }
