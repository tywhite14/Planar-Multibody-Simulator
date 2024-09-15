#pragma once

#include "Matrix.h"

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

	Type  m_type;
	unsigned int m_iPidx;	// point Pi
	unsigned int m_jPidx;	// point Pj
	unsigned int m_iBidx;	// body index i
	unsigned int m_jBidx;	// body index j
	unsigned int m_iUidx;	// unit vector u_i index
	unsigned int m_jUidx;	// unit vector u_j index
	unsigned int m_nConsts; // number of constraints
	unsigned int m_nBodies; // number of bodies involved
	Matrix<2, 3> Di;		// Body i jacobian
	Matrix<2, 3> Dj;		// Body j jacobian
	Matrix<2, 3> Di_dot;	// Body i jac_dot
	Matrix<2, 3> Dj_dot;	// Body j jac_dot

private:
	void initialize();
};
