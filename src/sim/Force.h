#pragma once

#include "Point.h"
#include "Vect2d.h"

enum forceType {
	none = 0,
	ptp,
	constant,
	rot,
	func
};

struct Force
{
	Force();
	Force(Vect2d& vec);
	Force(Point& A);
	Force(Point& A, Point& B);
	Force(Body& b);

	forceType type;
	Point iP;
	Point jP;
	Vect2d f;
	Vect2d fLocal;
	double dampingCoeff;
	double springConstant;
	double natLength;
	double T;
};
