#include "Joint.h"
#include "log.h"

Joint::Joint() :
	m_type(Type::none),
	m_nConsts(0),
	m_nBodies(0)
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

	for (int i = 0; i < m_nConsts; i++) {
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
