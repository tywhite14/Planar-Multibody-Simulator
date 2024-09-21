#include "SystemState.h"
#include "log.h"

SystemState::SystemState(unsigned int nBodies, unsigned int nConsts) :
	m_nBodies(nBodies),
	m_nConsts(nConsts),
	m_dof(3 * m_nBodies - m_nConsts),
	m_posDriftCoeff(10),
	m_velDriftCoeff(10),
	m_mechEnergy(0)
{
	Debug("SystemState created");
}

SystemState::~SystemState()
{
	Debug("SystemState destroyed");
}

void SystemState::initialize()
{
	m_dof = 3 * m_nBodies - m_nConsts;
}

void SystemState::update()
{

}

void SystemState::reset()
{
	
}
