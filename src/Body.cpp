#include "Body.h"

Body::Body() :
	mass(0.0),
	Moi(0.0),
	r(0.0),
	r_dot(0.0),
	phi(0.0),
	phi_dot(0.0),
	shape(animShape::none),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f),
	r_ddot(0.0),
	phi_ddot(0.0),
	netForce(0.0),
	netTorque(0.0)
{
}

Body::Body(
	double massIn,
	double MoiIn,
	Vect2d rIn,
	Vect2d r_dotIn,
	Vect2d phiIn,
	Vect2d phi_dotIn,
	animShape shapeIn,
	float animHeightIn,
	float animWidthIn,
	float animRadiusIn,
	Vect2d r_ddotIn,
	Vect2d phi_ddotIn,
	Vect2d netForceIn,
	Vect2d netTorqueIn
) :
	mass(massIn),
	Moi(MoiIn),
	r(rIn),
	r_dot(r_dotIn),
	phi(phiIn),
	phi_dot(phi_dotIn),
	shape(shapeIn),
	animHeight(animHeightIn),
	animWidth(animWidthIn),
	animRadius(animRadiusIn),
	r_ddot(r_ddotIn),
	phi_ddot(phi_ddotIn),
	netForce(netForceIn),
	netTorque(netTorqueIn)
{
}
