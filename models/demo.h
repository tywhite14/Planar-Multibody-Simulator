#pragma once

#include "PMS.h"

#include <cmath>

DEFINE_MODELS
{
	// BODIES ===============
	constexpr double L1 = 0.7;
	constexpr double M1 = 5.0;
	constexpr double PHI = c::PI_3;

	Body b1;
	b1.len  = L1;
	b1.mass = M1;
	b1.Moi  = 1.0/3.0 * M1 * L1 * L1;
	b1.r    = L1 / 2.0 * Vec2d(cos(PHI), sin(PHI));
	b1.phi  = c::PI_3;

	addBodies({ b1 });


	//// POINTS ===============
	Point A0(-1, Vec2d(0.0, 7.5));

	Point A1(0, Vec2d(-L1 / 2.0, 0.0));
	Point B1(0, Vec2d( L1 / 2.0, 0.0));

	addPoints({ A0, A1, B1 });


	//// JOINTS ===============
	Joint r1(Joint::Type::rev, 0, 1);

	addJoints({ r1 });


	//// FORCES ===============
	ForceGenerator F1;
	F1.bIdx = 0;

	addForces({ F1 });
	//applyGravity(true);
}
