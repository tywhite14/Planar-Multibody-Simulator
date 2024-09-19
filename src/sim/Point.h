#pragma once

#include "Matrix.h"

class Point
{
public:
	Point();
	Point(const Point& p);
	~Point();

	unsigned int bIdx;	// index of body in sysBodies with this point
	Matrix sP_local;	// relative coordinate in local frame
	Matrix sP;			// relative coordinate in global frame
	Matrix sP_dot;		// relative velocity in global frame
	Matrix sP_ddot;		// relative acceleration in global frame

private:
};
