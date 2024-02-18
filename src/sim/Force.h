#pragma once

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

	void apply(Vect2d location);
	Point getApplicationPoint() const;
	Point applicationPoint;
	Vect2d forceVector;
};
