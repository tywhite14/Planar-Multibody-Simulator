#pragma once

#include "PMS.h"

#include <cmath>

DEFINE_MODELS
{
	// BODIES ===============
	constexpr double L1 = 0.7;
	constexpr double M1 = 5.0;
	constexpr double PHI = c::PI_3;

	Body* b1 = new Body;
	b1->len  = L1;
	b1->mass = M1;
	b1->Moi  = 1.0/3.0 * M1 * L1 * L1;
	b1->r    = L1 / 2.0 * Vec2d(cos(PHI), sin(PHI));
	b1->phi  = c::PI_3;
	addBodies({ b1 });

	// POINTS ===============
	Point* A0 = new Point(Vec2d(0.0, 7.5));
	Point* A1 = new Point(Vec2d(-L1 / 2.0, 0.0), b1);
	Point* B1 = new Point(Vec2d( L1 / 2.0, 0.0), b1);
	addPoints({ A0, A1, B1 });

	// JOINTS ===============
	Revolute* r1 = new Revolute(A0, A1);
	addJoints({ r1 });

	// FORCES ===============
	ForceGenerator* F1 = new ForceGenerator;
	F1->B = b1;
	addForces({ F1 });
	applyGravity(true);
}
