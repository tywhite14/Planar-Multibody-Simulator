#pragma once

#include "Body.h"
#include "Vector.h"

class Point
{
public:
	Point(Vec2d localPos, Body* body = nullptr);
	Point(const Point& p);
	~Point();

	inline bool isOnGnd() const { return B == nullptr; }

	Body* B;			// reference to body the point is on
	Vec2d sP_local;		// relative coordinate in local frame
	Vec2d sP;			// relative coordinate in global frame
	Vec2d sP_dot;		// relative velocity in global frame
	Vec2d rP;			// global coordinate in global frame
	Vec2d rP_dot;		// global velocity in global frame

private:
};
