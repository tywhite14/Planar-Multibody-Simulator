#pragma once

#include "Body.h"
#include "Joint.h"
#include "Matrix.h"

#include <vector>

class SystemState
{
public:
	SystemState();
	~SystemState();

	void initialize();
	void update();
	void reset();

	inline int getDof() const { return m_dof; };
	void setDof();

	double kineticEnergy;
	double potentialEnergy;
	double mechEnergy;

	Matrix<3, 1> q;			// system state vector (px, py, phi)
	Matrix<3, 1> q_dot;		// 1st time derivative of system state
	Matrix<3, 1> q_ddot;	// 2nd time derivative of system state
	Matrix<3, 1> J;			// system Jacobian
	Matrix<3, 1> J_dot;		// 1st time derivative of system Jacobian
	Matrix<3, 1> W;			// inverse of system mass matrix
	Matrix<3, 1> h_a;		// array of net system applied forces
	Matrix<3, 1> h_r;		// array of net system reaction forces

private:
	unsigned int m_nBodies;	// number of bodies in the system
	unsigned int m_nConsts;	// number of constraints in the system
	unsigned int m_dof;		// degrees of freedom of the system
	double m_posDriftCoeff;	// coefficient of position drift
	double m_velDriftCoeff;	// coefficient of velocity drift
	double m_mechEnergy;	// total system mechanical energy

	void calcSystemEnergy();
	void formMassMatrices();
};
