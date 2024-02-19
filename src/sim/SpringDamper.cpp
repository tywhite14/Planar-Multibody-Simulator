#include "SpringDamper.h"
#include "log.h"

SpringDamper::SpringDamper() :
	originPoint(Point()),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	length(0.0)
{
	debug("SpringDamper created");
}

SpringDamper::SpringDamper(const Point& A, const Point& B) :
	originPoint(A),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	length(0.0)
{
	m_force.appliedPoint = B;
	m_calculateForce();
	debug("SpringDamper created");
}

void SpringDamper::m_calculateForce()
{
	Vect2d relativePosition = m_force.appliedPoint.rP - originPoint.rP;
	Vect2d relativeVelocity = m_force.appliedPoint.rP_dot - originPoint.rP_dot;

	Vect2d springForce =
		relativePosition.unit() * springConstant * (natLength - relativePosition.mag());

	Vect2d dampingForce = -relativeVelocity * dampingCoeff;

	setForce(Force(springForce + dampingForce, m_force.appliedPoint));
}

Force& SpringDamper::getForce()
{
	m_calculateForce();
	return m_force;
}
