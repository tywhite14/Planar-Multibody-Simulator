#include "log.h"
#include "Body.h"
#include "Point.h"

Point::Point() :
	rP(0),
	rP_dot(0),
	rP_ddot(0),
	sP_local(0)
{
	debug("Point created");
}

Point::Point(Body b, Vect2d sPlocal) :
	rP(0),
	rP_dot(0),
	rP_ddot(0),
	sP_local(sPlocal),
	bIndex(b.sysIndex)
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

void Point::onBody(Body& body)
{
	body.points.emplace_back(*this);
}