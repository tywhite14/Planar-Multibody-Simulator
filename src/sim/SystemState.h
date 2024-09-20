#pragma once

#include "Body.h"
#include "Joint.h"
#include "Matrix.h"

class SystemState
{
public:
	SystemState();
	SystemState(unsigned int nBodies, unsigned int nConsts);
	~SystemState();

	void initialize();
	void update();
	void reset();

	inline int getBodies() const { return m_nConsts; };
	inline int getConstraints() const { return m_nBodies; };
	inline int getDof() const { return m_dof; };
	inline double getMechEnergy() const { return m_mechEnergy; }

	Matrix q;		// system state vector (px, py, phi)
	Matrix q_dot;	// 1st time derivative of system state
	Matrix q_ddot;	// 2nd time derivative of system state
	Matrix J;		// system Jacobian
	Matrix J_dot;	// 1st time derivative of system Jacobian
	Matrix W;		// inverse of system mass matrix
	Matrix h_a;		// array of net system applied forces
	Matrix h_r;		// array of net system reaction forces

private:
	unsigned int m_nBodies;	// number of bodies in the system
	unsigned int m_nConsts;	// number of constraints in the system
	unsigned int m_dof;		// degrees of freedom of the system
	double m_posDriftCoeff;	// coefficient of position drift
	double m_velDriftCoeff;	// coefficient of velocity drift
	double m_mechEnergy;	// total system mechanical energy

	void calcSystemEnergy();
};
