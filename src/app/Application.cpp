#include "Application.h"
#include "log.h"

Application::Application(double rate, double fps) :
	m_nB(0),
	m_nP(0),
	m_nJ(0),
	m_nF(0),
	m_applyGravity(false),
	m_isRunning(true),
	m_rate(rate),
	m_fps(fps),
	m_1_rate(1.0/rate),
	m_1_fps(1.0/fps),
	m_timeEnd(1.0),
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
	for (auto b : m_bodies) { delete b; }
	for (auto p : m_points) { delete p;	}
	for (auto f : m_forces) { delete f; }
	for (auto j : m_joints) { delete j;	}

	Debug("Application destroyed");
}

void Application::initialize()
{
	// initialize application
	m_nB = (int) m_bodies.size();
	m_nP = (int) m_points.size();
	m_nJ = (int) m_joints.size();
	m_nF = (int) m_forces.size();

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
	for (int i = 0; i < m_nP; i++) {
		auto& p = *m_points.at(i);

		if (p.isOnGnd()) {
			continue;
		}
		
		// populate each body's point list
		auto& b = *m_bodies.at(p.bIdx);
		b.pointIndices.push_back(i);
	}

	// initialize points
	updatePoints();

	// initialize joints
	unsigned int row = 0;
	for (int i = 0; i < m_nJ; i++) {
		auto& j = *m_joints.at(i);

		switch (j.getType())
		{
		case (Joint::rev): {
			auto& r = *(Revolute*)m_joints.at(i);

			// simple error checking
			if (r.Pi->isOnGnd() && r.Pj->isOnGnd()) {
				FATAL("Defining revolute joint between ground and ground, dumbass.", -1);
			}

			// if defined by a point, populate which body that point belongs to
			if (!r.Pi->isOnGnd()) {
				r.Bi = m_bodies.at(r.Pi->bIdx);
				r.coli = 3 * r.Pi->bIdx;  // hella sus indexing
			}
			if (!r.Pj->isOnGnd()) {
				r.Bj = m_bodies.at(r.Pj->bIdx);
				r.colj = 3 * r.Pj->bIdx;  // hella sus indexing
			}

			r.updateJacobians();
			r.row = row;
			break;
		}
		default:
			Error("Joint type not defined yet");
		}

		row += j.getNumConstraints();
	}

	// initialize forces
	for (int i = 0; i < m_nF; i++) {
		auto& f = *m_forces.at(i);

		// TODO: actaully handle gravity

		if (!f.isPointDefined() && !f.isBodyDefined()) {
			Error("Ill-defined force");
		}

		else if (f.isPointDefined()) {
			auto& p = *f.P;
			
			// defined point, populate which body
			if (!f.isBodyDefined()) {
				f.B = m_bodies.at(p.bIdx);
			}

			// defined body and point on different body
			else if (f.isBodyDefined()) {
				if (f.B != m_bodies.at(p.bIdx)) {
					Error("Conflicing body definitions in force");
				}
			}
		}
	}

	// finish initializing system state
	for (int i = 0; i < m_nB; i++) {
		auto& b = *m_bodies.at(i);

		Matrix b_q =  {1, 2, 3};  //{ b.r.x, b.r.y, b.phi };
		Matrix b_qd = {1, 2, 3};  //{ b.r_dot.x, b.r_dot.y, b.phi_dot };

		int idx = 3 * i;
		for (int i = idx; i < idx+2; i++) {
			m_sysState.q(i) = b_q(i);
			m_sysState.q_dot(i) = b_qd(i);
		}

		m_sysState.W(idx, idx) = 1.0 / b.mass;
		m_sysState.W(idx+1, idx+1) = 1.0 / b.mass;
		m_sysState.W(idx+2, idx+2) = 1.0 / b.Moi;

		m_sysState.e_m += b.calcKineticEnergy();
		if (m_applyGravity) {
			// PE = m*g*h
			m_sysState.e_m += b.mass * m_gravAcc * b.r.y;
		}

		// that might have taken a while, reset internal clock
		m_clock.reset();
	}
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
	for (int i = 0; i < m_nP; i++) {
		auto& p = *m_points.at(i);

		if (p.isOnGnd()) {
			continue;
		}

		auto& b = *m_bodies.at(p.bIdx);
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
