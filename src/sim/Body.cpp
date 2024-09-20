#include "Body.h"
#include "constants.h"
#include "log.h"

Body::Body() :
	mass(0.0),
	Moi(0.0),
	r(0.0),
	r_dot(0.0),
	r_ddot(0.0),
	phi(0.0),
	phi_dot(0.0),
	phi_ddot(0.0),
	netAppliedForces(0.0),
	shape(anim::shape::none),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f)
{
	initialize();
}

Body::Body(const Body& b)
{
	*this = b;
	Debug("Body copied");
}

Body::~Body()
{
	Debug("Body destroyed");
}

void Body::initialize()
{

}

void Body::update()
{

}

double Body::calcKineticEnergy() const
{
	return 0.5 * mass * std::pow(r.magnitude(), 2);
}
