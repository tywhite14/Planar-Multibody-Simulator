#pragma once

#include <cmath>

#include "../src/PMS.h"

void Sim::_loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints)
{
	double L1 = 9.5;
	double L2 = 7.0;


	// BODIES ===============

	bodies.reserve(3);

	bodies.emplace_back(Body());

	Body b1 = Body();
	b1.mass = 12.0;
	b1.Moi = 22.6;
	b1.r = Vect2d(1.7, 3.0);
	b1.r_dot = Vect2d(0.0);
	b1.phi = math::PI_3;

	Body b2 = Body();
	b2.mass = 8.5;
	b2.Moi = 8.7;
	b2.r = Vect2d(6.4, 4.0);
	b2.r_dot = Vect2d(0.5);

	bodies.emplace_back(b1);
	bodies.emplace_back(b2);


	// POINTS ===============

	// Body 1 points

	Point A1 = Point(Vect2d( L1 / 2.0, 0.0));
	Point B1 = Point(Vect2d(-L1 / 2.0, 0.0));

	Point A2 = Point(Vect2d( L1 / 2.0, 0.0));
	Point B2 = Point(Vect2d(-L1 / 2.0, 0.0));

	b1.points.emplace_back(A1);
	b1.points.emplace_back(B1);

	b2.points.emplace_back(A2);
	b2.points.emplace_back(B2);


	// JOINTS ===============
	
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

	// FORCES ===============

	SpringDamper sd1;
	
	sd1.natLength = 1.2;
	sd1.dampingCoeff = 0.4;
	sd1.springConstant = 2200.0;
	
	sd1.iBindex = &b1;

	// b1.applyForce(sd1, 2);


}
