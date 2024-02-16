#include <cmath>
#include "../src/PMS.h"

void Sim::_loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	bodies.reserve(2);

	bodies.emplace_back(
		1.0,
		0.5,
		(1.0, 0.0),
		(1.0, 0.0),
		math::PI_3,
		0.0,
		anim::none
	);

	bodies.emplace_back(
		2.0,
		0.85,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);
}
