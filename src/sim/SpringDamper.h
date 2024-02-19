#pragma once

#include "ForceGenerator.h"
#include "Vect2d.h"

class SpringDamper : public ForceGenerator
{
public:
	SpringDamper();
	SpringDamper(const Point& A, const Point& B);
	Force& getForce() override;
	Point originPoint;
	double dampingCoeff;
	double springConstant;
	double natLength;

private:
	void m_calculateForce();
	double length;
};
