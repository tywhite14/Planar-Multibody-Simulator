#pragma once

#include "Vector.h"

class Point
{
public:
	Point(Vec2d localPos, int bidx = -1);
	Point(const Point& p);
	~Point();

	inline bool isOnGnd() const { return bIdx == -1; }

	int bIdx;			// index of body in sysBodies with this point
	Vec2d sP_local;		// relative coordinate in local frame
	Vec2d sP;			// relative coordinate in global frame
	Vec2d sP_dot;		// relative velocity in global frame
	Vec2d rP;			// global coordinate in global frame
	Vec2d rP_dot;		// global velocity in global frame

private:
};
