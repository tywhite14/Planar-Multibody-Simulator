#include "log.h"
#include "Body.h"

Body::Body() :
	mass(0.0),
	Moi(0.0),
	r(0.0),
	r_dot(0.0),
	phi(0.0),
	phi_dot(0.0),
	shape(anim::shape::none),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f),
	r_ddot(0.0),
	phi_ddot(0.0),
	netForce(0.0),
	netTorque(0.0)
{
	points.reserve(2);
	debug("Body created");
}

Body::Body(
	double massIn,
	double MoiIn,
	Vect2d rIn,
	Vect2d r_dotIn,
	double phiIn,
	double phi_dotIn,
	anim::shape shapeIn
) :
	mass(massIn),
	Moi(MoiIn),
	r(rIn),
	r_dot(r_dotIn),
	phi(phiIn),
	phi_dot(phi_dotIn),
	shape(shapeIn),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f),
	r_ddot(0.0),
	phi_ddot(0.0),
	netForce(0.0),
	netTorque(0.0)
{
	points.reserve(2);
	//forces.reserve(2);
	debug("Body created");
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

inline float Body::getAnimHeight() const { return animHeight; }
inline float Body::getAnimWidth()  const { return animWidth;  }
inline float Body::getAnimRadius() const { return animRadius; }
inline void  Body::setAnimHeight(const float sizeIn) { animHeight = sizeIn; }
inline void  Body::setAnimWidth (const float sizeIn) { animWidth = sizeIn;  }
inline void  Body::setAnimRadius(const float sizeIn) { animRadius = sizeIn; }
