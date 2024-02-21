#pragma once

#include "Point.h"
#include "Vect2d.h"

struct Force
{
	Force() : value(Vect2d()), appliedPoint(Point()) { }
	Force(const Vect2d& val, const Point& p = Point()) : value(val), appliedPoint(p) { }

	Vect2d value;
	Point appliedPoint;
};

class ForceGenerator
{
public:
	ForceGenerator();

	virtual Force& getForce() = 0;

protected:
	void setForce(const Force& f);
	Force m_force;
};
