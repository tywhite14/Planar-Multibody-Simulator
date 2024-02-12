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

private:
	std::vector<Body> _bodies;
	std::vector<Joint> _joints;
	unsigned int _dof;

	void loadModel(std::vector<Body>& bodies, std::vector<Joint>& joints);
};
