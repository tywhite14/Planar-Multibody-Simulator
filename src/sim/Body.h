#pragma once

#include <vector>

#include "Matrix.h"

class Body
{
public:
	Body();
	Body(const Body& b);
	~Body();

	void initialize();
	void update();

	// physical properties
	double mass;
	double Moi;
	double length;
	double mechEnergy;

	// state
	Matrix q;
	Matrix q_dot;
	Matrix q_ddot;
	Matrix netAppliedForces;

	std::vector<unsigned int> pointIndices;

	// animation
	anim::shape shape;
	float animHeight;
	float animWidth;
	float animRadius;

private:
};
