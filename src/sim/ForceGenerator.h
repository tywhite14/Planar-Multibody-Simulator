#pragma once

#include "Vector.h"

class ForceGenerator
{
public:
	ForceGenerator(unsigned int Pidx = -1);
	ForceGenerator(const ForceGenerator& f);
	~ForceGenerator();

	unsigned int pIdx;
	unsigned int bIdx;
	Vec3d value;

private:
};
