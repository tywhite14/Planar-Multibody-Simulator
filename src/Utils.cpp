#include <cmath>
#include "Matrix.h"
#include "Utils.h"

Vect2d rot(Vect2d vecIn, double angle)
{
	Matrix R(2, 2,
		{
		cos(angle), -sin(angle),
		sin(angle),  cos(angle) 
		});

	Matrix res(2, 1);


	Vect2d a;
	return a;
}

Vect2d local2global()
{
	Vect2d a;
	return a;
}

Vect2d global2local()
{
	Vect2d a;
	return a;
}
