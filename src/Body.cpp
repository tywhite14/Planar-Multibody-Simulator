#include "Body.h"

Body::Body() :

	// physical properties
	mass(0.0),
	Moi(0.0),

	// state
	r(0.0),
	r_dot(0.0),
	r_ddot(0.0),
	phi(0.0),
	phi_dot(0.0),
	phi_ddot(0.0),
	netForce(0.0),
	netTorque(0.0),

	// animation
	shape(none),
	animHeight(0.f),
	animWidth(0.f),
	animRadius(0.f)
{

}
