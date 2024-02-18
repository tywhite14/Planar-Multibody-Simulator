#include <cmath>

#include "Force.h"
#include "log.h"

Force::Force()
{
	debug("Force created");
}

Force::Force(Vect2d fIn)
{
	debug("Force created");
}

Force::Force(double a, double b)
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
