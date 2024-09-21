#include "Point.h"
#include "log.h"

Point::Point(unsigned int bidx, Vec2d localPos) : bIdx(bidx), sP_local(localPos)
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
