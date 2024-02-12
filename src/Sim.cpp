#include "log.h"
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
	loadModel(_bodies, _joints);
	// construct mass matrix and inv mass matrix

	// gather up all points from bodies?

	// gather all unit vectors?
}

void Sim::update()
{
	// gather all forces?

	// solve EOM
	
}

void Sim::finalize()
{
	
}

void Sim::reset()
{
	
}

int Sim::getDof() const
{
	return _dof;
}

void Sim::setDof()
{
	_dof = _bodies.size() * 3;

	for (auto& joint : _joints)
	{
		if (joint.type == jointType::rev)
		{
			_dof -= 2;
		}
		else if (joint.type == jointType::tran)
		{
			_dof -= 2;
		}
		else if (joint.type == jointType::rigid)
		{
			_dof -= 3;
		}
		else if (joint.type == jointType::rel_rot)
		{
			warn("This is incorrect. Update");
			_dof -= 2;
		}
	}
}
