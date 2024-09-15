#include "Point.h"
#include "log.h"

Point::Point() :
	bIdx(0),
	sP_local(2, 1),
	sP(2, 1),
	sP_dot(2, 1),
	sP_ddot(2, 1)
{
	Debug("Point created");
}

Point::Point(const Point& p)
{
	*this = p;
	Debug("Point copied");
}

Point::~Point()
{
	Debug("Point destroyed");
}
