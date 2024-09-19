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
	void update();
	void render();

	std::vector<Body>  m_bodies;
	std::vector<Joint> m_joints;
	std::vector<ForceGenerator> m_forces;
	SystemState m_systemState;

	const double m_rate;	// Hz, update rate system physics
	const double m_1_rate;  // sec, inverse of rate
	const double m_fps;		// Hz, update rate of rendering
	const double m_1_fps;	// sec, inverse of render rate
	const double m_timeEnd; // sec, temporary variable, time to end sim
	double m_frameTime;		// sec, time between the last frame
	bool m_isRunning;
	SystemClock m_simClock;
};
