#include "../src/Utils.h"
#include "../src/PMS.h"

void Sim::_loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	bodies.reserve(2);

	bodies.emplace_back(
		1.0,
		0.5,
		Vect2d(1.0, 0.0),
		Vect2d(1.0, 0.0),
		PI / 3.0,
		0.0,
		anim::none
	);

	bodies.emplace_back(
		2.0,
		0.85,
		Vect2d(0.0, 1.2),
		Vect2d(-0.20, 0.4),
		PI / 10.0,
		0.0,
		anim::circle
	);
}
