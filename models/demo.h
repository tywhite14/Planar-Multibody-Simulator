#include <cmath>
#include "../src/PMS.h"

void Sim::_loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	double L1 = 0.12;
	double L2 = 0.25;

	bodies.reserve(12);

	bodies.emplace_back(
		1.0,
		0.1,
		(1.0, 0.0),
		(1.0, 0.0),
		math::PI_3,
		0.0,
		anim::none
	);

	bodies.emplace_back(
		2.0,
		0.2,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		3.0,
		0.3,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		1.0,
		0.1,
		(1.0, 0.0),
		(1.0, 0.0),
		math::PI_3,
		0.0,
		anim::none
	);

	bodies.emplace_back(
		2.0,
		0.2,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		3.0,
		0.3,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		1.0,
		0.1,
		(1.0, 0.0),
		(1.0, 0.0),
		math::PI_3,
		0.0,
		anim::none
	);

	bodies.emplace_back(
		2.0,
		0.2,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		3.0,
		0.3,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		1.0,
		0.1,
		(1.0, 0.0),
		(1.0, 0.0),
		math::PI_3,
		0.0,
		anim::none
	);

	bodies.emplace_back(
		2.0,
		0.2,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.emplace_back(
		3.0,
		0.3,
		(0.0, 1.2),
		(-0.20, 0.4),
		math::PI / 10.0,
		0.0,
		anim::circle
	);

	bodies.at(0).points.emplace_back(Vect2d(0,  L1 / 2.0));
	bodies.at(0).points.emplace_back(Vect2d(0, -L1 / 2.0));

	bodies.at(1).points.emplace_back(Vect2d(0,  L2 / 2.0));
	bodies.at(1).points.emplace_back(Vect2d(0, -L2 / 2.0));
}
