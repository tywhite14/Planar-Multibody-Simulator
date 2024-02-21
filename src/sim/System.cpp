#include "log.h"
#include "System.h"
#include "Clock.h"

#pragma warning(disable : 4267)

System::System() : _nBodies(0), _dof(0), isRunning(true), g(9.8)
{
	note("System created");
	sysBodies.reserve(4);
	sysJoints.reserve(5);
	sysForces.reserve(3);	
}

System::~System()
{
	debug("System destroyed");
	delete(this);
}

void System::initialize()
{
	sysBodies.emplace_back(gnd);

	_loadModel(sysBodies, sysJoints);
	debug("Model loaded");

	_nBodies = sysBodies.size() - 1;
	setDof();

	_formMassMatrices();
	//_formSystemJacobian();
	//_formSystemCoeff();
}

void System::update()
{
	// calculate force from each FG and add it to forces vector
	for (auto& FG : sysFGs)
	{
		sysForces.emplace_back(FG->getForce());
	}

	//_formSystemRhs();
	//_solveSystemEquation();
	//_integrate(double dt);
	finalize();
}

void System::finalize()
{
	isRunning = false;
	note("Shutting down sim");
}

void System::reset()
{
	
}

int System::getDof() const
{
	return _dof;
}

void System::setDof()
{
	_dof = _nBodies * 3;

	for (auto& joint : sysJoints)
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
			warn("rel_rot not fully developed yet. Results are incorrect");
			_dof -= 2;
			break;
		default:
			error("Undefined joint type");
		}
	}
}

void System::applyGravity(bool flag)
{
	if (!flag)
		return;

	Force gravity(Vect2d(0, -g));

	for (Body& b : sysBodies)
	{
		b.appliedForces.emplace_back(gravity);
	}
}

void System::addBodies(std::initializer_list<Body> bodiesIn)
{
	for (Body b : bodiesIn)
	{
		b.sysIndex = sysBodies.size();
		sysBodies.emplace_back(b);
	}
}

void System::addPoints(std::initializer_list<Point> pointsIn)
{
	for (auto& p : pointsIn)
	{
		auto bod = sysBodies.at(p.bIndex);
		bod.points.emplace_back(p);
	}
}

void System::addJoints(std::initializer_list<Joint> jointsIn)
{
	for (auto& j : jointsIn)
	{
		sysJoints.emplace_back(j);
	}
}

void System::addForces(std::vector<ForceGenerator*> FGsIn)
{
	for (auto& fg : FGsIn)
	{
		Force force = fg->getForce();
		auto& bod = sysBodies.at(force.appliedPoint.bIndex);
		bod.appliedForces.emplace_back(force);
	}
}

//	PRIVATE

void System::_formMassMatrices()
{
	const unsigned int nB3 = sysBodies.size() * 3;
	M    = Matrix(nB3);
	M_inv = Matrix(nB3);

	for (unsigned int i = 0; i < nB3; i++)
	{
		int idx = (nB3 + 1) * i;
		if ((idx+1) % 3 ==  0) {
			M(idx) = sysBodies.at(i / 3).Moi;
			M_inv(idx) = 1.0 / sysBodies.at(i / 3).Moi;
		}
		else {
			M(idx) = sysBodies.at(i / 3).mass;
			M_inv(idx) = 1.0 / sysBodies.at(i / 3).mass;
		}
	}
}
