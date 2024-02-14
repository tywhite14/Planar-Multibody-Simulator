#pragma once
#include "Vect2d.h"

struct Point
{
	Vect2d rP;			// global coordinate
	Vect2d rP_dot;		// global velocity
	Vect2d rP_ddot;		// global acceleration
	Vect2d sP_local;    // local coordinate
	int bodyIdx;		// reference body index
	
	Point() :
		rP(0),
		rP_dot(0),
		rP_ddot(0),
		sP_local(0),
		bodyIdx(0)
	{ /* VOID */ }
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

struct Frame
{
	Vect2d i, j;
	Vect2d x, y;

	Frame() :
		i(0), j(0)
	{ /* VOID */ }
};
