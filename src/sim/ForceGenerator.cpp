#include "ForceGenerator.h"
#include "log.h"

ForceGenerator::ForceGenerator() : m_pIdx(0), m_bIdx(0), value({ 0 })
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
