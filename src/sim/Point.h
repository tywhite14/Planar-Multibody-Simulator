#pragma once

#include "Vector.h"

class Point
{
public:
	Point(unsigned int bidx = -1, Vec2d localPos = {0, 0});
	Point(const Point& p);
	~Point();

	unsigned int bIdx;	// index of body in sysBodies with this point
	Vec2d sP_local;		// relative coordinate in local frame
	Vec2d sP;			// relative coordinate in global frame
	Vec2d sP_dot;		// relative velocity in global frame
	Vec2d sP_ddot;		// relative acceleration in global frame

private:
};
