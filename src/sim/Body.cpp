#include "log.h"
#include "Body.h"

Body::Body() :
	mass(0.0),
	Moi(0.0),
	r(0.0),
	r_dot(0.0),
	phi(0.0),
	phi_dot(0.0),
	netAppliedForce(0.0),
	netAppliedTorque(0.0),
	shape(anim::shape::none),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f),
	r_ddot(0.0),
	phi_ddot(0.0),
	sysIndex(0)
{
	initialize();
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
	netAppliedForce(0.0),
	netAppliedTorque(0.0),
	shape(shapeIn),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f),
	r_ddot(0.0),
	phi_ddot(0.0),
	sysIndex(0)
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
	points.reserve(3);

	Point CoM;
	CoM.rP = this->r;
	CoM.rP_dot = this->r_dot;
	CoM.rP_ddot = this->r_ddot;
	CoM.sP_local = Vect2d(0);
	points.push_back(CoM);

	debug("Body created");
}

void Body::update()
{
	// write the update for each attribute!
}

inline float Body::getAnimHeight() const { return animHeight; }
inline float Body::getAnimWidth()  const { return animWidth;  }
inline float Body::getAnimRadius() const { return animRadius; }
inline void  Body::setAnimHeight(const float sizeIn) { animHeight = sizeIn; }
inline void  Body::setAnimWidth (const float sizeIn) { animWidth = sizeIn;  }
inline void  Body::setAnimRadius(const float sizeIn) { animRadius = sizeIn; }
