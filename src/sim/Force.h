#pragma once

#include "Vect2d.h"

class Force
{
public:
	Vect2d asRect();
	double mag;
	double angle;
	Vect2d point;  // point of application
};
