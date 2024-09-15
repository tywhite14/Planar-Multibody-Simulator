#include "Application.h"
#include "log.h"

Application::Application(double rate, double fps) :
	m_rate(rate), m_fps(fps), m_isRunning(true)
{
	debug("Application created");
}

Application::~Application()
{
	debug("Application destroyed");
}

void Application::run()
{
	finalize();
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
		sysBodies.emplace_back(b);
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
		sysJoints.emplace_back(j);
	}
}

void Application::addForces(std::initializer_list<ForceGenerator> forcesIn)
{
	for (auto& f : forcesIn)
	{
		sysForces.emplace_back(f);
	}
}
