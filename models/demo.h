#pragma once

#include <cmath>

#include "../src/PMS.h"

void System::loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	double L1 = 9.5;
	double L2 = 7.0;


	// BODIES ===============

	Body b1;
	b1.mass = 12.0;
	b1.Moi = 22.6;
	b1.r = Vect2d(1.7, 3.0);
	b1.r_dot = Vect2d(0.0);
	b1.phi = math::PI_3;

	Body b2;
	b2.mass = 8.5;
	b2.Moi = 8.7;
	b2.r = Vect2d(6.4, 4.0);
	b2.r_dot = Vect2d(0.5);

	addBodies({ b1, b2 });


	// POINTS ===============
	Point C0(gnd, Vect2d(0.0, 7.5));

	Point A1(b1, Vect2d(-L1 / 2.0, 0.0));
	Point B1(b1, Vect2d( L1 / 2.0, 0.0));

	Point A2(b2, Vect2d(-L2 / 2.0, 0.0));
	Point B2(b2, Vect2d( L2 / 2.0, 0.0));

	addPoints({ C0, A1, B1, A2, B2 });


	// JOINTS ===============
	
	Joint r1(B1, A2, joint::rev);
	Joint r2(A1, C0, joint::rev);

	addJoints({ r1, r2 });

	// FORCES ===============

	Force f1;
	f1.type = forceType::constant;
	f1.f = Vect2d(5, 0);

	Force sd1(C0, A1);
	sd1.type = forceType::ptp;
	sd1.dampingCoeff = 0.5;
	sd1.springConstant = 850;
	sd1.natLength = 1.0;

	addForces({ f1, sd1 });
	applyGravity(true);
}
