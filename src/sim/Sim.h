#pragma once

#include <vector>

#include "Body.h"
#include "Joint.h"
#include "Matrix.h"
#include "Point.h"

class Sim
{
public:
	Sim();
	~Sim();

	void initialize();
	void update();
	void finalize();
	void reset();

	int getDof() const;
	void setDof();

	std::vector<Body>  bodies;
	std::vector<Joint> joints;
	bool isRunning;

private:
	unsigned short _dof;
	double gravity;
	Matrix massMatrix;
	Matrix invMassMatrix;
	Matrix sysState;
	Matrix forcesApplied;
	Matrix forcesReaction;

	void _loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints);
	void _formMassMatrices();
};
