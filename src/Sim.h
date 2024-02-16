#pragma once

#include <vector>

#include "Body.h"
#include "Joint.h"
#include "Matrix.h"
#include "Structs.h"

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
	unsigned int _nBodies;
	unsigned int _nJoints;
	Matrix massMatrix;
	Matrix invMassMatrix;

	void _loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints);
	void _formMassMatrices();
};
