#include "log.h"
#include "Sim.h"

Sim::Sim() : _dof(0)
{
	//bodies.push_back(Body());   // create ground
	loadModel(bodies, joints);
	log("Model loaded");
}

Sim::~Sim()
{
	log("Sim destroyed");
}

void Sim::initialize()
{
	// construct mass matrix and inv mass matrix

	// gather up all points from bodies?

	// gather all unit vectors?
}

void Sim::update()
{
	setDof();

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
	_dof = (bodies.size() - 0) * 3;

	for (auto& joint : joints)
	{
		switch (joint.type)
		{
		case (rev):
			_dof -= 2;
			break;
		case(tran):
			_dof -= 2;
			break;
		case(rigid):
			_dof -= 3;
			break;
		case(rel_rot):
			warn("This is incorrect. Update");
			_dof -= 2;
			break;
		default:
			error("Undefined joint type");
		}
	}
}
