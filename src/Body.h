#pragma once
#include <vector>
#include "Structs.h"

class Body
{
public:
	Body();
	Body(
		double massIn,
		double MoiIn,
		Vect2d rIn,
		Vect2d r_dotIn,
		Vect2d phiIn,
		Vect2d phi_dotIn,
		animShape shapeIn,
		float animHeightIn,
		float animWidthIn,
		float animRadiusIn,
		Vect2d r_ddotIn,
		Vect2d phi_ddotIn,
		Vect2d netForceIn,
		Vect2d netTorqueIn
	);

	// physical properties
	double mass;
	double Moi;

	// state
	Vect2d r;
	Vect2d r_dot;
	Vect2d phi;
	Vect2d phi_dot;

	std::vector<Point> points;

	// animation
	animShape shape;
	float animHeight;
	float animWidth;
	float animRadius;

private:
	Vect2d r_ddot;
	Vect2d phi_ddot;
	Vect2d netForce;
	Vect2d netTorque;
};
