#include "SpringDamper.h"

Vect2d SpringDamper::getNetForce()
{
	Vect2d relativePosition = applicationPoint.rP - originPoint.rP;
	Vect2d relativeVelocity = applicationPoint.rP_dot - originPoint.rP_dot;

	Vect2d springForce =
		relativePosition.unit() * springConstant * (natLength - relativePosition.mag());

	Vect2d dampingForce = -relativeVelocity * dampingCoeff;

	return springForce + dampingForce;
}
