#pragma once

#include "Body.h"
#include "Joint.h"
#include "Point.h"
#include "SystemState.h"
#include "ForceGenerator.h"

#include <vector>

#define DEFINE_MODELS void Application::loadModels()

#define DBG_APP
#ifdef  DBG_APP
#define DGB_APP_CALL(x) x
#else
#define DGB_APP_CALL(x)
#endif

class Application
{
public:
	Application(double rate = 1000, double fps = 75);
	~Application();

	void run();
	void finalize();

	void loadModels();
	inline void addBodies(std::initializer_list<Body>  bodiesIn) { m_bodies = bodiesIn; }
	inline void addPoints(std::initializer_list<Point> pointsIn) { m_points = pointsIn; }
	inline void addJoints(std::initializer_list<Joint> jointsIn) { m_joints = jointsIn; }
	inline void addForces(std::initializer_list<ForceGenerator> forcesIn) { m_forces = forcesIn; }

	inline bool isRunning() const { return m_isRunning; }

private:
	void update();
	void render();

	std::vector<Body>  m_bodies;
	std::vector<Point> m_points;
	std::vector<Joint> m_joints;
	std::vector<ForceGenerator> m_forces;
	SystemState m_systemState;

	const double m_rate;	// Hz, update rate system physics
	const double m_1_rate;  // sec, inverse of rate
	const double m_fps;		// Hz, update rate of rendering
	const double m_1_fps;	// sec, inverse of render rate
	const double m_timeEnd; // sec, temporary variable, time to end sim
	double m_time;		// sec, time of the previous frame
	double m_updateTimer;
	double m_renderTimer;
	bool m_isRunning;
	Clock m_clock;

	// debugging
	DGB_APP_CALL(unsigned long m_updateCounter);
	DGB_APP_CALL(unsigned long m_renderCounter);
};