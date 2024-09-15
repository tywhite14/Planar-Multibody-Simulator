#include "Point.h"
#include "log.h"

Point::Point() :
	bIdx(0),
	sP_local(0),
	sP(0),
	sP_dot(0),
	sP_ddot(0)
{
	debug("Point created");
}

Point::Point(const Point& p)
{
	*this = p;
	debug("Point copied");
}

Point::~Point()
{
	debug("Point destroyed");
}
