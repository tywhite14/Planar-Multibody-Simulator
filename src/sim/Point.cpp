#include "log.h"
#include "Point.h"

Point::Point() :
	rP(0),
	rP_dot(0),
	rP_ddot(0),
	sP_local(0)
{
	debug("Point created");
}

Point::Point(Vect2d sPlocal) :
	rP(0),
	rP_dot(0),
	rP_ddot(0),
	sP_local(sPlocal)
{ 
	debug("Point created");
}

Point::~Point()
{
	debug("Point copied");
}

Point::Point(const Point& p)
{
	*this = p;
	debug("Point destroyed");
}
