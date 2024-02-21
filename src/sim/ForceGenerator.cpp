#include "ForceGenerator.h"
#include "log.h"

ForceGenerator::ForceGenerator() : m_force(Force())
{
	debug("ForceGenerator created");
}

void ForceGenerator::setForce(const Force& f)
{
	m_force = f;
}
