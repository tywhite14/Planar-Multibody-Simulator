#pragma once

#include "Point.h"

class Point;

struct Force
{
	Force();
	Force(const Vect2d& val);
	Force(const Vect2d& val, const Point& p);

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
