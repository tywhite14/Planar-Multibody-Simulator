#include "Joint.h"
#include "log.h"

Joint::Joint(Type type, unsigned int iPidx, unsigned int jPidx) :
	m_type(type),
	m_nConsts(0),
	m_nBodies(0),
	m_iPidx(iPidx),
	m_jPidx(jPidx),
	m_iBidx(-1),
	m_jBidx(-1),
	m_iUidx(-1),
	m_jUidx(-1)
{ 
	switch (m_type)
	{
	case (Type::rev):
		m_nConsts = 2;
		m_nBodies = 2;
		break;

	case(Type::tran):
		m_nConsts = 2;
		m_nBodies = 2;
		break;

	case(Type::rigid):
		m_nConsts = 3;
		m_nBodies = 2;
		break;

	case(Type::none):
		FATAL("Undefined joint type", -1);
	}

	for (unsigned int i = 0; i < m_nConsts; i++) {
		m_constraints.push_back({});
	}

	Debug("Joint created");
}

Joint::Joint(const Joint& j)
{
	*this = j;
	Debug("Joint destroyed");
}

Joint::~Joint()
{
	Debug("Joint copied");
}
