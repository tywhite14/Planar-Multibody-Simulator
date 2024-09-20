#pragma once

#include "Matrix.h"

#include <vector>

struct  Constraint
{
	Constraint() :
		m_iPidx(0),
		m_jPidx(0),
		m_iBidx(0),
		m_jBidx(0),
		m_iUidx(0),
		m_jUidx(0)
	{

	}


	Matrix D;				// Body j jacobian
	Matrix D_dot;			// Body i jac_dot
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

	Joint();
	Joint(const Joint& j);
	~Joint();
	
	inline unsigned int getNumConstraints() const { return m_nConsts; }
	inline unsigned int getNumBodies() const { return m_nBodies; }
	inline Type getType() const { return m_type; }

private:
	Type m_type;
	unsigned int m_nConsts; // number of constraints
	unsigned int m_nBodies; // number of bodies involved
	unsigned int m_iPidx;	// point Pi
	unsigned int m_jPidx;	// point Pj
	unsigned int m_iBidx;	// body index i
	unsigned int m_jBidx;	// body index j
	unsigned int m_iUidx;	// unit vector u_i index
	unsigned int m_jUidx;	// unit vector u_j index

	std::vector<Constraint> m_constraints;
};
