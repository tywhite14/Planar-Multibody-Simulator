#include "Joint.h"
#include "log.h"

Joint::Joint() :
	type(jointType::none),
	iBindex(0),
	jBindex(0),
	iPindex(0),
	jPindex(0),
	iUindex(0),
	jUindex(0),
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
	debug("Joint destroyed");
}

void Joint::_initialize()
{
	switch (type)
	{
	case (rev):
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(tran):

		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(rigid):
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	case(rel_rot):
		warn("rel_rot not fully developed yet. Results are incorrect");
		DconstMat = Matrix(0);
		Jacobian = Matrix(0);
		Rhs = Matrix(0);
		break;

	default:
		error("Undefined joint type");
	}
}
