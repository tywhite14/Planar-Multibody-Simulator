#include "Application.h"
#include "log.h"

Application::Application(double rate, double fps) :
	m_rate(rate),
	m_1_rate(1.0/rate),
	m_fps(fps),
	m_1_fps(1.0/fps),
	m_timeEnd(1.0),
	m_frameTime(0.0),
	m_isRunning(true)
{
	loadModels();
	Debug("Application created");
}

Application::~Application()
{
	Debug("Application destroyed");
}

void Application::run()
{
	print("ENTERED RUN");
	exit(4);
	m_frameTime = m_clock.restart();

	if (m_frameTime >= m_1_rate) {
		update();
	}
	if (m_frameTime >= m_1_fps) {
		render();
	}
	if (m_clock.getSeconds() > m_timeEnd) {
		finalize();
	}
}

void Application::finalize()
{
	m_isRunning = false;
	print("Shutting down application");
}

void Application::update()
{
	Debug("Application updated");
}

void Application::render()
{
	Debug("Application rendered");
}
