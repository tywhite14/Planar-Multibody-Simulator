#pragma once

#include "Body.h"
#include "Point.h"
#include "Vect2d.h"

class Force
{
public:
	Force();
	Force(const Vect2d& fIn);
	Force(Vect2d& fIn, Point& appPoint);
	Force(double a, double b, Point& appPoint);
	Force(const Force& f);
	~Force();

	void apply(Point& location);

	Point applicationPoint;
	unsigned int iBindex;
	Vect2d value;
};
