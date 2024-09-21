#include "Application.h"
#include "log.h"

Application::Application(double rate, double fps) :
	m_rate(rate),
	m_1_rate(1.0/rate),
	m_fps(fps),
	m_1_fps(1.0/fps),
	m_timeEnd(3.0),
	m_time(0.0),
	m_updateTimer(0.0),
	m_renderTimer(0.0),
	m_isRunning(true)
{
	loadModels();
	Debug("Application created");
	DGB_APP_CALL(m_updateCounter = 0);
	DGB_APP_CALL(m_renderCounter = 0);
}

Application::~Application()
{
	Debug("Application destroyed");
}

void Application::run()
{
	m_time = m_clock.getSeconds();

	// exit sim
	if (m_time > m_timeEnd) {
		finalize();
	}

	// update physics
	while (m_time - m_updateTimer >= m_1_rate) {
		m_updateTimer += m_1_rate;
		update();
	}

	// render graphics
	if (m_time - m_renderTimer >= m_1_fps) {
		m_renderTimer += m_1_fps;
		render();
	}
}

void Application::finalize()
{
	m_isRunning = false;
	print("Shutting down application");
	DGB_APP_CALL(print("Updates: " << m_updateCounter));
	DGB_APP_CALL(print("Renders: " << m_renderCounter));
}

void Application::update()
{
	DGB_APP_CALL(m_updateCounter++);
}

void Application::render()
{
	print("Application rendered");
	DGB_APP_CALL(m_renderCounter++);
}
