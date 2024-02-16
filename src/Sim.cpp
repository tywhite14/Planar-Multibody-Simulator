#include "log.h"
#include "Sim.h"
#include "Clock.h"

Sim::Sim() : _dof(0), _nBodies(0), _nJoints(0), isRunning(true)
{
	//bodies.push_back(Body());   // create ground
	Clock timer;
	_loadModel(bodies, joints);
	
	//debug("Model loaded");

	_nBodies = bodies.size();
	_nJoints = joints.size();

	_formMassMatrices();
	std::cout << "Timer took " << timer.getElapsedTime() << std::endl;

	debug(massMatrix);
	debug(invMassMatrix);

	// gather up all points from bodies?
	// calcGlobalPointPos();

	// gather all unit vectors?
	// calcUnitVectors();

}

Sim::~Sim()
{
	debug("Sim destroyed");
}

void Sim::initialize()
{
}

void Sim::update()
{
	setDof();

	// gather all forces?

	// solve EOM
	finalize();
}

void Sim::finalize()
{
	isRunning = false;
	debug("Shutting down sim");
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


//	PRIVATE

void Sim::_formMassMatrices()
{
	const unsigned int nB3 = _nBodies * 3;
	massMatrix    = Matrix(nB3);
	invMassMatrix = Matrix(nB3);

	for (int i = 0; i < nB3; i++)
	{
		int idx = (nB3 + 1) * i;
		if ((idx+1) % 3 ==  0) {
			massMatrix(idx) = bodies.at(i / 3).Moi;
			invMassMatrix(idx) = 1.0 / bodies.at(i / 3).Moi;
		}
		else {
			massMatrix(idx) = bodies.at(i / 3).mass;
			invMassMatrix(idx) = 1.0 / bodies.at(i / 3).mass;
		}
	}
}
