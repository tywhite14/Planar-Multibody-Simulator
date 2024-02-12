#pragma once

#include <vector>
#include "Structs.h"
#include "Body.h"

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
};
