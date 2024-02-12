#pragma once
#include <vector>
#include "Structs.h"
// #include <SFML/Graphics.hpp>

class Body
{
	// physical properties
	double mass;
	double Moi;

	// state
	Vect2d r;
	Vect2d r_dot;
	Vect2d r_ddot;
	Vect2d phi;
	Vect2d phi_dot;
	Vect2d phi_ddot;
	Vect2d netForce;
	Vect2d netTorque;

	std::vector<Point> points;
	

	// animation
	animShape shape;
	float animHeight;
	float animWidth;
	float animRadius;

public:
	Body();
};
