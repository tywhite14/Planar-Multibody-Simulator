#pragma once

#include <vector>

#include "Body.h"
#include "ForceGenerator.h"
#include "Joint.h"
#include "Matrix.h"
#include "Point.h"

class System
{
public:
	System();
	~System();

	void initialize();
	void update();
	void finalize();
	void reset();

	int getDof() const;
	void setDof();

	void applyGravity(bool flag);
	
	void addBodies(std::initializer_list<Body>  bodiesIn);
	void addPoints(std::initializer_list<Point> pointsIn);
	void addJoints(std::initializer_list<Joint> jointsIn);
	void addForces(std::initializer_list<ForceGenerator> FGsIn);

	Body gnd;
	std::vector<Body>  sysBodies;
	std::vector<Joint> sysJoints;
	std::vector<ForceGenerator*> sysFGs;

	double kineticEnergy;
	double potentialEnergy;
	double totalEnergy;

	bool isRunning;

private:
	unsigned int _nBodies;	// number of bodies in the system
	unsigned short _dof;	// degrees of freedom of the system
	const double g;			// acceleration due to gravity
	Matrix M;				// system mass matrix
	Matrix M_inv;			// inverse of system mass matrix
	Matrix c;				// system coordinates
	Matrix c_dot;			// 1st time derivative of system coordinates
	Matrix c_ddot;			// 2nd time derivative of system coordinates
	Matrix h_A;				// array of net system applied forces
	Matrix h_R;				// array of net system reaction forces
	Matrix coeffMat;		// coefficient matrix of the system
	Matrix D;				// system Jacobian
	Matrix D_dot;			// 1st time derivative of system Jacobian
	Matrix lagranges;		// system Lagrange multipliers
	Matrix sysRhs;			// right-hand side of system equation
	
	// coeffMat(M, D)						[bodies and joints]
	// sysRhs(h_A, D_dot, c_dot)			[forces and joints]
	// sysState = inv(coeffMat) * sysRhs	[bodies , joints, and bodies]

	void _calcKineticEnergy();
	void _calcPotentialEnergy();
	void _calcTotalEnergy();
	void _loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints);
	void _formMassMatrices();
};
