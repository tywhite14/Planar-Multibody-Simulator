#pragma once

#include <vector>

#include "Body.h"
#include "Joint.h"
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

private:
	unsigned short _dof;

	void loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints);
};
