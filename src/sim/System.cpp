#include "log.h"
#include "System.h"
#include "Clock.h"

#pragma warning(disable : 4267)

System::System() : _dof(0), isRunning(true), g(0.0, -9.8)
{
	note("System created");

	bodies.reserve(4);
	joints.reserve(5);
	forces.reserve(3);

	bodies.emplace_back(gnd);

	_loadModel(bodies, joints);
	debug("Model loaded");

	setDof();

	_formMassMatrices();
	//_formSystemJacobian();
	//_formSystemCoeff();
	
}

System::~System()
{
	debug("System destroyed");
	delete(this);
}

void System::initialize()
{
}

void System::update()
{
	setDof();

	// calculate force from each FG and add it to forces vector
	for (auto& FG : FGs)
	{
		forces.emplace_back(FG->getForce());
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
			warn("rel_rot not fully developed yet. Results are incorrect");
			_dof -= 2;
			break;
		default:
			error("Undefined joint type");
		}
	}
}

//void System::applyForce(const Force& f, Body& b)
//{
//	// add f to sim.forces vector
//	forces.emplace_back(f);
//
//	// add f pointer to b.forces
//	b.forces.emplace_back(&forces.at(0));
//}
//
//void System::applyForce(Force& f, Point& p)
//{
//	f.applicationPoint = p;
//	Body& b = bodies.at(p.bIndex);
//}

void System::applyGravity(bool flag)
{
	if (!flag)
		return;

	//Force gravity(g);

	for (Body& b : bodies)
	{
		//applyForce(gravity, b);
	}
}

void System::addBodies(std::initializer_list<Body> bodiesIn)
{
	for (Body b : bodiesIn)
	{
		b.sysIndex = bodies.size();
		bodies.emplace_back(b);
	}
}

void System::addPoints(std::initializer_list<Point> pointsIn)
{
	for (auto& p : pointsIn)
	{
		auto bod = bodies.at(p.bIndex);
		bod.points.emplace_back(p);
	}
}

void System::addJoints(std::initializer_list<Joint> jointsIn)
{
	for (auto& j : jointsIn)
	{
		joints.emplace_back(j);
	}
}


//	PRIVATE

void System::_formMassMatrices()
{
	const unsigned int nB3 = bodies.size() * 3;
	M    = Matrix(nB3);
	M_inv = Matrix(nB3);

	for (unsigned int i = 0; i < nB3; i++)
	{
		int idx = (nB3 + 1) * i;
		if ((idx+1) % 3 ==  0) {
			M(idx) = bodies.at(i / 3).Moi;
			M_inv(idx) = 1.0 / bodies.at(i / 3).Moi;
		}
		else {
			M(idx) = bodies.at(i / 3).mass;
			M_inv(idx) = 1.0 / bodies.at(i / 3).mass;
		}
	}
}
