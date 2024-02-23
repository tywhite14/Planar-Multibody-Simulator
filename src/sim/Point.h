#pragma once

#include "Vect2d.h"

class Body;

struct Point
{
	Point();
	Point(Body b, Vect2d sPlocal);
	Point(const Point& p);
	~Point();

	unsigned int bIndex;	// index of body in sysBodies with this point
	Vect2d rP;				// global coordinate
	Vect2d rP_dot;			// global velocity
	Vect2d rP_ddot;			// global acceleration
	Vect2d sP_local;		// local coordinate
};
