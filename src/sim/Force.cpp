#include "Force.h"
#include "log.h"

class Body;

Force::Force() :
	type(forceType::none),
	iP(Point()),
	jP(Point()),
	f(Vect2d()),
	fLocal(Vect2d()),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	T(0.0)
{
	debug("Force Created");
}

Force::Force(Vect2d& vec) :
	type(forceType::none),
	iP(Point()),
	jP(Point()),
	f(vec),
	fLocal(Vect2d()),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	T(0.0)
{
	debug("Force Created");
}


Force::Force(Point& A) :
	type(forceType::none),
	iP(A),
	jP(Point()),
	f(Vect2d()),
	fLocal(Vect2d()),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	T(0.0)
{
	debug("Force Created");	
}

Force::Force(Point& A, Point& B) :
	type(forceType::ptp),
	iP(A),
	jP(B),
	f(Vect2d()),
	fLocal(Vect2d()),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	T(0.0)
{

	debug("Force Created");
}

Force::Force(Body& b) :
	type(forceType::constant),
	iP(Point()),
	jP(Point()),
	f(Vect2d()),
	fLocal(Vect2d(0, 0)),
	dampingCoeff(0.0),
	springConstant(0.0),
	natLength(0.0),
	T(0.0)
{

	debug("Force Created");
}
