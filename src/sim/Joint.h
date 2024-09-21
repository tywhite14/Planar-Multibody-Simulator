#pragma once

#include "Matrix.h"

#include <vector>

struct  Constraint
{
	Constraint()
	{	}

	//Matrix D;				// Body j jacobian
	//Matrix D_dot;			// Body i jac_dot
};

class Joint
{
public:
	enum Type
	{
		none = 0,
		rev,
		tran,
		roll,
		rigid
	};

	Joint(Type type = Type::none, unsigned int ipidx = -1, unsigned int jpidx = -1);
	Joint(const Joint& j);
	~Joint();
	
	inline unsigned int getNumConstraints() const { return m_nConsts; }
	inline unsigned int getNumBodies() const { return m_nBodies; }
	inline Type getType() const { return m_type; }

	unsigned int iPidx;	// point Pi
	unsigned int jPidx;	// point Pj
	unsigned int iBidx;	// body index i
	unsigned int jBidx;	// body index j
	unsigned int iUidx;	// unit vector u_i index
	unsigned int jUidx;	// unit vector u_j index

private:
	Type m_type;
	unsigned int m_nConsts; // number of constraints
	unsigned int m_nBodies; // number of bodies involved

	std::vector<Constraint> m_constraints;
};
