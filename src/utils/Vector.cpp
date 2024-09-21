#include "Vector.h"
#include "log.h"

#include <iomanip>
#include <stdlib.h>

Vec2d::Vec2d() : x(0.0), y(0.0) { }
Vec2d::Vec2d(const double s) : x(s), y(s) { }
Vec2d::Vec2d(const double xi, const double yi) : x(xi), y(yi) {}

Vec2d Vec2d::random() const
{
	double x, y;
	x = (double) rand() / RAND_MAX;
	y = (double) rand() / RAND_MAX;
	return (x, y);
}

Vec2d Vec2d::randi(const int max, bool pm) const
{
	double x, y;

	if (pm) {
		x = rand() % (2 * (max + 1)) - max;
		y = rand() % (2 * (max + 1)) - max;
		return (x, y);
	}

	x = rand() % (max + 1);
	y = rand() % (max + 1);
	return (x, y);
}

Vec2d Vec2d::operator=(const std::initializer_list<double>& list)
{
	if (list.size() != 2) {
		FATAL("Initializer list is not the same size as matrix.", 9);
	}
	
	x = *list.begin();
	y = *list.end();
	return (x, y);
}

std::ostream& operator<<(std::ostream& os, const Vec2d& v)
{
	os << v.x << ", " << v.y;
	return os;
}
