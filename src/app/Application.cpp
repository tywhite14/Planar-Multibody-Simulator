#include "Application.h"
#include "log.h"

Application::Application(double rate, double fps) :
	m_nB(0),
	m_nP(0),
	m_nJ(0),
	m_nF(0),
	m_isRunning(true),
	m_rate(rate),
	m_fps(fps),
	m_1_rate(1.0/rate),
	m_1_fps(1.0/fps),
	m_timeEnd(3.0),
	m_time(0.0),
	m_updateTimer(0.0),
	m_renderTimer(0.0)
{
	DGB_APP_CALL(m_updateCounter = 0);
	DGB_APP_CALL(m_renderCounter = 0);
	Debug("Application created");
	
	loadModels();
	initialize();
}

Application::~Application()
{
	Debug("Application destroyed");
}

void Application::initialize()
{
	// initialize application
	m_nB = m_bodies.size();
	m_nP = m_points.size();
	m_nJ = m_joints.size();
	m_nF = m_forces.size();

	// initialize system state
	m_sysState.nBodies	= m_nB;
	m_sysState.q		= Matrix::zeros(3 * m_nB, 1);
	m_sysState.q_dot	= Matrix::zeros(3 * m_nB, 1);
	m_sysState.q_ddot	= Matrix::zeros(3 * m_nB, 1);
	m_sysState.W		= Matrix::zeros(3 * m_nB);
	m_sysState.h_a		= Matrix::zeros(3 * m_nB, 1);
	m_sysState.h_r		= Matrix::zeros(3 * m_nB, 1);
	m_sysState.k_c		= 20;
	m_sysState.k_c_dot	= 20;

	// initialize bodies
	for (int i = 0; i < m_points.size(); i++) {
		auto& p = m_points.at(i);

		if (p.isOnGnd())
			continue;

		// populate each body's point list
		m_bodies.at(p.bIdx).pointIndices.push_back(i);
	}

	// initialize points
	updatePoints();

	// initialize joints
	// this one's gonna suck
	for (auto& j : m_joints) {
		auto& pi = m_points.at(j.iPidx);
		auto& pj = m_points.at(j.jPidx);

		// if defined by a point, populate which body that point belongs to
		if (pi.isOnGnd() && !pj.isOnGnd()) {
			j.iBidx = m_points.at(j.iPidx).bIdx;
		}
		
	}

	// initialize forces

	// finish initializing system state

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

void Application::updateBodies()
{
}

void Application::updatePoints()
{
	for (auto& p : m_points) {
		if (p.isOnGnd()) {
			continue;
		}

		auto& b = m_bodies.at(p.bIdx);
		p.sP = p.sP_local.rotate(b.phi);
		p.sP_dot = p.sP.rot90() * b.phi_dot;
		p.rP = b.r + p.sP;
		p.rP_dot = b.r_dot + p.sP_dot;
	}
}

void Application::updateJoints()
{
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
