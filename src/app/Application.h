#pragma once

#include "Body.h"
#include "Joint.h"
#include "Point.h"
#include "SystemState.h"
#include "ForceGenerator.h"

#include <vector>

class Application
{
public:
	Application(double rate = 1000, double fps = 75);
	~Application();

	void run();
	void finalize();

	void addBodies(std::initializer_list<Body>  bodiesIn);
	void addPoints(std::initializer_list<Point> pointsIn);
	void addJoints(std::initializer_list<Joint> jointsIn);
	void addForces(std::initializer_list<ForceGenerator> forcesIn);

	inline bool isRunning() const { return m_isRunning; }

private:
	std::vector<Body>  sysBodies;
	std::vector<Joint> sysJoints;
	std::vector<ForceGenerator> sysForces;
	SystemState m_systemState;

	double m_rate;
	double m_fps;
	bool m_isRunning;
};
