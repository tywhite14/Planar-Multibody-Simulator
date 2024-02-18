#pragma once

#include "Matrix.h"
#include "Point.h"

enum jointType
{
	none = 0,
	rev,
	tran,
	rel_rot,
	rel_tran,
	roll,
	rigid
};

class Joint
{
public:
	jointType type;			// see constants.h for types
	unsigned int iBindex;	// body index i
	unsigned int jBindex;	// body index j
	unsigned int iPindex;	// point Pi index
	unsigned int jPindex;	// point Pj index
	unsigned int iUindex;	// unit vector u_i index
	unsigned int jUindex;	// unit vector u_j index

	Matrix DconstMat;		// (Eq. 7.1)
	Matrix Jacobian;		// (Eq. 7.4)
	Matrix Rhs;				// (Eq. 7.7)

	Joint();
	~Joint();
	Joint(const Joint& j);

private:
	void _initialize();
};
