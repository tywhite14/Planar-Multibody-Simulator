#pragma once

#include "Body.h"
#include "Vect2d.h"

class Point
{
public:
	Vect2d rP;			// global coordinate
	Vect2d rP_dot;		// global velocity
	Vect2d rP_ddot;		// global acceleration
	Vect2d sP_local;    // local coordinate
	unsigned int bIndex;

	Point();
	Point(Body b, Vect2d sPlocal);
	~Point();
	Point(const Point& p);
	
	void onBody(Body& body);
};
