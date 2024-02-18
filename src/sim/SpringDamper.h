#pragma once

#include "Force.h"
#include "Vect2d.h"

class SpringDamper : public Force
{
public:
	Vect2d getNetForce();

	double springConstant;
	double dampingCoeff;
	double natLength;
	double length;
	Point originPoint;
};

