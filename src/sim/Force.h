#pragma once

#include "Body.h"
#include "Point.h"
#include "Vect2d.h"

class Force
{
public:
	Force();
	Force(Vect2d fIn);
	Force(double a, double b);
	~Force();
	Force(const Force& f);

	void apply(Point& location);

	Point applicationPoint;
};
