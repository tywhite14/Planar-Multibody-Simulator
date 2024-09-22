#include "SystemState.h"
#include "log.h"

SystemState::SystemState() :
	nBodies(0),
	nConsts(0),
	m_dof(0),
	k_c(10),
	k_c_dot(10),
	e_m(0)
{
	Debug("SystemState created");
}

SystemState::~SystemState()
{
	Debug("SystemState destroyed");
}

void SystemState::initialize()
{
	m_dof = 3 * nBodies - nConsts;
}

void SystemState::update()
{

}

void SystemState::reset()
{
	
}
