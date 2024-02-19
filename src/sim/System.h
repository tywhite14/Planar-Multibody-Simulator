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

	//void applyForce(Force& f, Body& b);		 // applies force f to CoM of body b
	//void applyForce(Force& f, Point& p); // applies force f to point p
	void applyGravity(bool flag);
	
	void addBodies(std::initializer_list<Body> bodiesIn);
	void addPoints(std::initializer_list<Point> pointsIn);
	void addJoints(std::initializer_list<Joint> jointsIn);

	Body gnd;
	std::vector<Body>  bodies;
	std::vector<Joint> joints;
	std::vector<Force> forces;
	std::vector<ForceGenerator*> FGs;

	double kineticEnergy;
	double potentialEnergy;
	double totalEnergy;

	bool isRunning;

private:
	unsigned short _dof;	// degrees of freedom of the system
	const Vect2d g;			// acceleration due to gravity
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

	void _loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints);
	void _formMassMatrices();
};
