#include "../src/PMS.h"

void Sim::loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	Body b1;

	b1.mass = 1;
	b1.Moi = 1;
	b1.r = 1;
	b1.r_dot = 1;
	b1.phi = 1;
	b1.phi_dot = 1;
}