#include "Sim.h"

Sim::Sim() : _dof(0)
{
	_bodies.push_back(Body());   // create ground
}

Sim::~Sim()
{
	
}

void Sim::initialize()
{
	// construct mass matrix and inv mass matrix

	// gather up all points from bodies?

	// gather all unit vectors?

	// gather all forces?


}

void Sim::update()
{
	
}

void Sim::finalize()
{
	
}

void Sim::reset()
{
	
}

int Sim::getDof()
{
	return 69;
}

void Sim::setDof()
{
	_dof = _bodies.size() * 3; // update later
}
