#include "Application.h"
#include "log.h"

Application::Application(double rate, double fps) :
	m_rate(rate),
	m_1_rate(1.0/rate),
	m_fps(fps),
	m_1_fps(1.0/fps),
	m_frameTime(0.0),
	m_timeEnd(1.0), 
	m_isRunning(true)
{
	Debug("Application created");
}

Application::~Application()
{
	Debug("Application destroyed");
}

void Application::run()
{
	m_frameTime = m_simClock.getSecondsDecimal() - m_frameTime;
	if (m_frameTime >= m_1_rate) {
		update();
	}
	if (m_frameTime >= m_1_fps) {
		render();
	}
	if (m_simClock.getSecondsDecimal() > m_timeEnd) {
		finalize();
	}
}

void Application::finalize()
{
	m_isRunning = false;
	print("Shutting down application");
}

void Application::addBodies(std::initializer_list<Body> bodiesIn)
{

	for (Body b : bodiesIn)
	{
		m_bodies.emplace_back(b);
	}
}

void Application::addPoints(std::initializer_list<Point> pointsIn)
{
	for (auto& p : pointsIn)
	{
		//bod.points.emplace_back(p);
	}
}

void Application::addJoints(std::initializer_list<Joint> jointsIn)
{
	for (auto& j : jointsIn)
	{
		m_joints.emplace_back(j);
	}
}

void Application::addForces(std::initializer_list<ForceGenerator> forcesIn)
{
	for (auto& f : forcesIn)
	{
		m_forces.emplace_back(f);
	}
}

void Application::update()
{
	Debug("Application updated");
}

void Application::render()
{
	Debug("Application rendered");
}
