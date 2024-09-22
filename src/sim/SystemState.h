#pragma once

#include "Body.h"
#include "Joint.h"
#include "Matrix.h"

class SystemState
{
public:
	SystemState();
	~SystemState();

	void initialize();
	void update();
	void reset();

	inline int getDof() const { return m_dof; };

	unsigned int nBodies;	// number of bodies in the system
	unsigned int nConsts;	// number of constraints in the system
	double k_c;				// coefficient of position drift correction
	double k_c_dot;			// coefficient of velocity drift correction
	double e_m;				// total system mechanical energy

	Matrix q;		// system state vector (px, py, phi)
	Matrix q_dot;	// 1st time derivative of system state
	Matrix q_ddot;	// 2nd time derivative of system state
	Matrix J;		// system Jacobian
	Matrix J_dot;	// 1st time derivative of system Jacobian
	Matrix W;		// inverse of system mass matrix
	Matrix h_a;		// vector of net system applied forces
	Matrix h_r;		// vector of net system reaction forces
	Matrix f_d;		// system drift force vector

private:
	unsigned int m_dof;		// degrees of freedom of the system

};
