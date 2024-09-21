#pragma once

#include "Matrix.h"
#include "Vector.h"
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
	double mass;		// mass
	double Moi;			// moment of inertia
	double len;			// length

	// state
	Vec2d r;			// position vector
	Vec2d r_dot;		// velocity vector
	Vec2d r_ddot;		// acceleration vector

	double phi;			// angle
	double phi_dot;		// angular velocity
	double phi_ddot;	// angular acceleration

	Matrix h_a;			// net applied forces/torques

	std::vector<unsigned int> pointIndices;

	// animation
	anim::shape shape;
	float animHeight;
	float animWidth;
	float animRadius;

private:
};
