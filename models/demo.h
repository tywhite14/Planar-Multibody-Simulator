#pragma once

#include <cmath>

#include "../src/PMS.h"

void Sim::_loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	double L1 = 0.12;
	double L2 = 0.25;

	// BODIES

	bodies.reserve(3);

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

	// Body 1 points
	bodies.at(0).points.emplace_back(Vect2d(0,  L1 / 2.0));
	bodies.at(0).points.emplace_back(Vect2d(0, -L1 / 2.0));
	;
	// Body 2 points
	bodies.at(1).points.emplace_back(Vect2d(0,  L2 / 2.0));
	bodies.at(1).points.emplace_back(Vect2d(0, -L2 / 2.0));


	//// JOINTS
	//joints.reserve(2);

	//Joint r1;
	//Joint r2;

	//r1.type = jointType::rev;
	//r1.iBindex = 0;
	//r1.jBindex = 1;
	//r1.iPindex = 0;
	//r1.jPindex = 0;

	//r2.type = jointType::rev;
	//r2.iBindex = 1;
	//r2.jBindex = 2;
	//r2.iPindex = 1;
	//r2.jPindex = 0;

	//joints.emplace_back(r1);
	//joints.emplace_back(r2);
}
