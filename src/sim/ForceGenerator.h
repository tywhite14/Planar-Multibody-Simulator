#pragma once

#include "Matrix.h"

class ForceGenerator
{
public:
	ForceGenerator(unsigned int Pidx = -1);
	ForceGenerator(const ForceGenerator& f);
	~ForceGenerator();

	unsigned int pIdx;
	unsigned int bIdx;
	Matrix value;

private:
};
