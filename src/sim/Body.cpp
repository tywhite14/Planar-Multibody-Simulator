#include "Body.h"
#include "log.h"

Body::Body() :
	mass(0.0),
	Moi(0.0),
	q(0.0),
	q_dot(0.0),
	q_ddot(0.0),
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
	debug("Body copied");
}

Body::~Body()
{
	debug("Body destroyed");
}

void Body::initialize()
{

}

void Body::update()
{

}
