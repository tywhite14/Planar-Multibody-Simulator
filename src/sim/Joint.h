#pragma once

#include "Matrix.h"
#include "Point.h"

namespace joint
{
	enum type
	{
		none = 0,
		rev,
		tran,
		rel_rot,
		rel_tran,
		roll,
		rigid
	};
}

class Joint
{
public:
	joint::type type;		// see constants.h for types
	Point iP;				// point Pi
	Point jP;				// point Pj
	unsigned int iBindex;	// body index i
	unsigned int jBindex;	// body index j
	unsigned int iUindex;	// unit vector u_i index
	unsigned int jUindex;	// unit vector u_j index
	unsigned int numConstraints;
	Matrix DconstMat;		// (Eq. 7.1)
	Matrix Jacobian;		// (Eq. 7.4)
	Matrix Rhs;				// (Eq. 7.7)

	Joint();
	Joint(Point& A, Point& B, joint::type typeIn);
	~Joint();
	Joint(const Joint& j);

	void connect(Point& A, Point& B, joint::type typeIn);

private:
	void _initialize();
};
