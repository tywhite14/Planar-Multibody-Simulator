#include "Joint.h"
#include "log.h"

Joint::Joint() :
	m_type(Type::none),
	m_iPidx(0),
	m_jPidx(0),
	m_iBidx(0),
	m_jBidx(0),
	m_iUidx(0),
	m_jUidx(0),
	m_nConsts(0),
	m_nBodies(0)
{ 
	initialize();
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

void Joint::initialize()
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
		Error("Undefined joint type");
	}
}
