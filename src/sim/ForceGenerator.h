#pragma once

#include "Matrix.h"

class ForceGenerator
{
public:
	ForceGenerator();
	ForceGenerator(const ForceGenerator& f);
	~ForceGenerator();

	unsigned int m_pIdx;
	unsigned int m_bIdx;
	Matrix value;

private:
};
