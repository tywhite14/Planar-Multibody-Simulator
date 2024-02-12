#pragma once

#include "Structs.h"

enum jointType
{
	rev = 0,
	tran,
	rel_rot,
	rigid
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

	Joint();
};
