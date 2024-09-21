#include "ForceGenerator.h"
#include "log.h"

ForceGenerator::ForceGenerator(unsigned int Pidx) : pIdx(Pidx), bIdx(-1)
{
	Debug("ForceGenerator created");
}

ForceGenerator::ForceGenerator(const ForceGenerator& fg)
{
	*this = fg;
	Debug("ForceGenerator copied");
}

ForceGenerator::~ForceGenerator()
{
	Debug("ForceGenerator destroyed");
}
