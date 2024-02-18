#include <cmath>

#include "Force.h"
#include "log.h"

Force::Force() : forceVector(0)
{
	debug("Force created");
}

Force::Force(Vect2d fIn) : forceVector(0)
{
	debug("Force created");
}

Force::Force(double a, double b) : forceVector(0)
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

void Force::apply(Vect2d location)
{
	applicationPoint = location;
}

Point Force::getApplicationPoint() const
{
	return applicationPoint;
}
