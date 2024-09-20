#pragma once

#include "Matrix.h"

#include <vector>

class Body
{
public:
	Body();
	Body(const Body& b);
	~Body();

	void initialize();
	void update();

	double calcKineticEnergy() const;

	// physical properties
	double mass;
	double Moi;
	double length;

	// TODO: Just make a damn Vec2d/Vec3d class
	// state
	Matrix r;
	Matrix r_dot;
	Matrix r_ddot;

	double phi;
	double phi_dot;
	double phi_ddot;

	Matrix netAppliedForces;

	std::vector<unsigned int> pointIndices;

	// animation
	anim::shape shape;
	float animHeight;
	float animWidth;
	float animRadius;

private:
};
