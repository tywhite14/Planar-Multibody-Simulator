#include "ForceGenerator.h"
#include "log.h"

ForceGenerator::ForceGenerator(Point* p) : P(p), B(nullptr)
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
