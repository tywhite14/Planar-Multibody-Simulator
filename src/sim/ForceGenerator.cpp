#include "ForceGenerator.h"
#include "log.h"

ForceGenerator::ForceGenerator() : m_pIdx(0), m_bIdx(0), value({ 0 })
{
	debug("ForceGenerator created");
}

ForceGenerator::ForceGenerator(const ForceGenerator& fg)
{
	*this = fg;
	debug("ForceGenerator copied");
}

ForceGenerator::~ForceGenerator()
{
	debug("ForceGenerator destroyed");
}
