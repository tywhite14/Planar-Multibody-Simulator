#define _USE_MATH_DEFINES

#include <math.h>
#include "../src/PMS.h"

void Sim::loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	Body b1;
	b1.mass    = 1.0;
	b1.Moi     = 0.5;
	b1.r       = Vect2d(1.0, 0.0);
	b1.r_dot   = Vect2d(1.0, 0.0);
	b1.phi     = M_PI / 3.0;
	b1.phi_dot = 0.0;

	Body b2;
	b2.mass    = 3.0;
	b2.Moi     = 0.75;
	b2.r       = Vect2d(0.0, 1.0);
	b2.r_dot   = Vect2d(0.0, -0.2);
	b2.phi     = -M_PI / 10.0;
	b2.phi_dot = 0.10;

	bodies.push_back(b1);
	bodies.push_back(b2);
}
