#pragma once

#include "Force.h"
#include "Vect2d.h"

class SpringDamper : public Force
{
public:
	Vect2d getNetForce();

private:
	double springConstant;
	double dampingCoeff;
	double natLength;
	double netForce;
	double length;
	Point originPoint;
};

