#pragma once
#include "Vect2d.h"

struct Point
{
	Vect2d rP;			// global coordinate
	Vect2d rP_dot;		// global velocity
	Vect2d rP_ddot;		// global acceleration
	Vect2d sP_local;    // local coordinate
	int bodyIdx;		// reference body index
	
	Point() :
		rP(0),
		rP_dot(0),
		rP_ddot(0),
		sP_local(0),
		bodyIdx(0)
	{ /* VOID */ }
};

enum jointType
{
	rev = 0,
	tran,
	rel_rot,
	rigid
};

enum animShape
{
	none = 0,
	circle,
	rect,
	line
};

struct Joint
{
	jointType type;			// rev, tran, ...
	unsigned int iBindex;	// body index i
	unsigned int jBindex;	// body index j
	unsigned int iPindex;	// point Pi index
	unsigned int jPindex;	// point Pj index
	unsigned int iUindex;	// unit vector u_i index
	unsigned int jUindex;	// unit vector u_j index

	Joint() :
		type(rev),
		iBindex(0),
		jBindex(0),
		iPindex(0),
		jPindex(0),
		iUindex(0),
		jUindex(0)
	{ /* VOID */ }
}; 

struct Frame
{
	Vect2d i, j;
	Vect2d x, y;

	Frame() :
		i(0), j(0)
	{ /* VOID */ }
};
