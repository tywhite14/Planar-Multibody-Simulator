#pragma once
#include "Vect2d.h"

struct Point
{
	Vect2d rP;			// global coordinate
	Vect2d rP_dot;		// global velocity
	Vect2d rP_ddot;		// global acceleration
	Vect2d sP_local;    // local coordinate

	Point() :
		rP(0),
		rP_dot(0),
		rP_ddot(0),
		sP_local(0)
	{ }
	Point(Vect2d sPlocal) :
		rP(0),
		rP_dot(0),
		rP_ddot(0),
		sP_local(sPlocal)
	{ }
};

namespace anim {
	enum shape
	{
		none = 0,
		circle,
		rect,
		line
	};
}
