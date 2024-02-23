#include "Joint.h"
#include "log.h"

Joint::Joint() :
	type(joint::type::none),
	iP(Point()),
	jP(Point()),
	iBindex(0),
	jBindex(0),
	iUindex(0),
	jUindex(0),
	numConstraints(0),
	DconstMat(Matrix()),
	Jacobian(Matrix()),
	Rhs(Matrix())
{ 
	_initialize();
	debug("Joint created");
}

Joint::Joint(Point& A, Point& B, joint::type typeIn) :
	type(typeIn),
	iP(A),
	jP(B),
	iBindex(A.bIndex),
	jBindex(B.bIndex),
	iUindex(0),
	jUindex(0),
	numConstraints(0),
	DconstMat(Matrix()),
	Jacobian(Matrix()),
	Rhs(Matrix())
{
	_initialize();
	debug("Joint created");
}

Joint::~Joint()
{
	debug("Joint copied");
}

Joint::Joint(const Joint& j)
{
	*this = j;
	debug("Joint destroyed");
}

void Joint::connect(Point& A, Point& B, joint::type typeIn)
{
	type = typeIn;
	iP = A;
	jP = B;
	iBindex = A.bIndex;
	jBindex = B.bIndex;

	_initialize();
}

void Joint::_initialize()
{
	switch (type)
	{
	case (joint::type::rev):
		numConstraints = 2;
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(joint::type::tran):
		numConstraints = 2;
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(joint::type::rigid):
		numConstraints = 3;
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(joint::type::rel_rot):
		numConstraints = 0;
		error("rel_rot not fully developed yet. Results are incorrect");
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(joint::type::none):
	default:
		error("Undefined joint type");
	}
}
