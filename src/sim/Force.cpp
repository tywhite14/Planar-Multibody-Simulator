#include <cmath>

#include "Force.h"
#include "log.h"

Force::Force() : value(0)
{
	debug("Force created");
	warn("Don't actually use the default Force() constructor. Need an application point.");
}

Force::Force(Vect2d& fIn) : value(fIn), applicationPoint(Point())
{
	debug("Force created");
}

Force::Force(Vect2d& fIn, Point& appPoint) : value(fIn), applicationPoint(appPoint)
{
	debug("Force created");
}

Force::Force(double a, double b, Point& appPoint) : value(a, b), applicationPoint(appPoint)
{
	debug("Force created");
}

Force::~Force()
{
	debug("Force destroyed");
}

Force::Force(const Force& f)
{
	*this = f;
	debug("Force copied");
}

void Force::apply(Point& location)
{
	applicationPoint = location;
}
