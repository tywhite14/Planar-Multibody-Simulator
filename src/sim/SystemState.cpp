#include "SystemState.h"
#include "log.h"

SystemState::SystemState() :
	m_nBodies(0), 
	m_dof(0)
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
