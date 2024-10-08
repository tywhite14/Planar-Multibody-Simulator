#include "Vector.h"
#include "log.h"

#include <iomanip>
#include <stdlib.h>

// ========================= Vect2d ========================= //
Vec2d::Vec2d(const double s) : x(s), y(s) { }
Vec2d::Vec2d(const double xi, const double yi) : x(xi), y(yi) {}

Vec2d Vec2d::random() const
{
	double x, y;
	x = (double)rand() / RAND_MAX;
	y = (double)rand() / RAND_MAX;
	return Vec2d(x, y);
}

Vec2d Vec2d::randi(const int max, bool pm) const
{
	double x, y;

	if (pm) {
		x = rand() % (2 * (max + 1)) - max;
		y = rand() % (2 * (max + 1)) - max;
		return Vec2d(x, y);
	}

	x = rand() % (max + 1);
	y = rand() % (max + 1);
	return Vec2d(x, y);
}

Vec2d Vec2d::operator=(const std::initializer_list<double>& list)
{
	if (list.size() != 2) {
		FATAL("Initializer list is not the same size as matrix.", 9);
	}

	x = *list.begin();
	y = *list.end();
	return Vec2d(x, y);
}

std::ostream& operator<<(std::ostream& os, const Vec2d& v)
{
	os << v.x << ", " << v.y;
	return os;
}


// ========================= Vect3d ========================= //
Vec3d::Vec3d(const double s) : x(s), y(s), z(s) { }
Vec3d::Vec3d(const double xi, const double yi, const double zi) : x(xi), y(yi), z(zi) {}

Vec3d Vec3d::random() const
{
	double x, y, z;
	x = (double) rand() / RAND_MAX;
	y = (double) rand() / RAND_MAX;
	z = (double) rand() / RAND_MAX;
	return Vec3d(x, y, z);
}

Vec3d Vec3d::randi(const int max, bool pm) const
{
	double x, y, z;

	if (pm) {
		x = rand() % (2 * (max + 1)) - max;
		y = rand() % (2 * (max + 1)) - max;
		z = rand() % (2 * (max + 1)) - max;
		return Vec3d(x, y, z);
	}

	x = rand() % (max + 1);
	y = rand() % (max + 1);
	z = rand() % (max + 1);
	return Vec3d(x, y, z);
}

Vec3d Vec3d::operator=(const std::initializer_list<double>& list)
{
	if (list.size() != 3) {
		FATAL("Initializer list is not the same size as matrix.", 9);
	}

	x = *list.begin();
	y = *(list.begin() + 1);
	y = *list.end();
	return Vec3d(x, y, z);
}

std::ostream& operator<<(std::ostream& os, const Vec3d& v)
{
	os << v.x << ", " << v.y << ", " << v.z;
	return os;
}
