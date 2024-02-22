#include "ForceGenerator.h"
#include "log.h"

Force::Force() : value(Vect2d()), appliedPoint(Point()) { }
Force::Force(const Vect2d& val) : value(val), appliedPoint(Point()) { }
Force::Force(const Vect2d& val, const Point& p) : value(val), appliedPoint(p) { }


ForceGenerator::ForceGenerator() : m_force(Force())
{
	debug("ForceGenerator created");
}

void ForceGenerator::setForce(const Force& f)
{
	m_force = f;
}

Force& ForceGenerator::getForce()
{
	return m_force;
}