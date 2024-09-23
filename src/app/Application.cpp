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
	m_timeEnd(0.2),
	m_time(0.0),
	m_updateTimer(0.0),
	m_renderTimer(0.0)
{
	DGB_APP_CALL(m_updateCounter = 0);
	DGB_APP_CALL(m_renderCounter = 0);
	Debug("Application created");
	
	loadModels();
	print("Models loaded");
	initialize();
}

Application::~Application()
{
	for (auto& b : m_bodies) { delete b; }
	for (auto& p : m_points) { delete p; }
	for (auto& f : m_forces) { delete f; }
	for (auto& j : m_joints) { delete j; }

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

	// initialize bodies with point indices
	for (int i = 0; i < m_nP; i++) {
		const Point& p = *m_points.at(i);

		if (p.isOnGnd())
			continue;

		auto& b = *p.B;
		b.pointIndices.push_back(i);
	}

	updatePoints();

	// initialize joints
	for (const Joint* j : m_joints) {

		switch (j->getType())
		{
		case (Joint::rev): {
			Revolute& r = *(Revolute*)j;

			// simple error checking
			if (r.Pi->isOnGnd() && r.Pj->isOnGnd()) {
				FATAL("Defining revolute joint between ground and ground, dumbass.", -1);
			}

			r.updateJacobians();
			r.row = m_sysState.nConsts;
			m_sysState.nConsts += r.getNumConstraints();
			break;
		}
		default:
			FATAL("Joint type not defined yet", -1);
		}
	}

	// initialize forces
	for (ForceGenerator* f : m_forces) {

		// TODO: actaully handle gravity

		if (!f->isPointDefined() && !f->isBodyDefined()) {
			FATAL("Ill-defined force", -1);
		}

		else if (f->isPointDefined()) {
			const Point& p = *f->P;
			
			// defined point, populate which body
			if (!f->isBodyDefined()) {
				f->B = p.B;
			}

			// defined body and point on different body
			else if (f->isBodyDefined()) {
				if (f->B != p.B) {
					FATAL("Conflicing body definitions in force", 1);
				}
			}
		}
	}

	// finish initializing system state
	for (int i = 0; i < m_nB; i++) {
		const Body& b = *m_bodies.at(i);

		const Matrix b_q = b.r;
		const Matrix b_qd = b.r_dot;

		int idx = 3 * i;
		for (int ii = idx; ii < idx+2; ii++) {
			m_sysState.q(ii) = b_q(ii);
			m_sysState.q_dot(ii) = b_qd(ii);
		}

		m_sysState.W(idx, idx) = 1.0 / b.mass;
		m_sysState.W(idx+1, idx+1) = 1.0 / b.mass;
		m_sysState.W(idx+2, idx+2) = 1.0 / b.Moi;

		m_sysState.e_m += b.calcKineticEnergy();
		if (m_applyGravity) {
			m_sysState.e_m += b.mass * m_gravAcc * b.r.y; // PE = m*g*h
		}

		// now that we know number of constraints, finish initializing system state
		const int nC = m_sysState.nConsts;
		m_sysState.J	 = Matrix::zeros(3 * nC, 3 * m_nB);
		m_sysState.J_dot = Matrix::zeros(3 * nC, 3 * m_nB);
		m_sysState.f_d	 = Matrix::zeros(3 * nC, 1);

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

void Application::update()
{
	DGB_APP_CALL(m_updateCounter++);

	// zero out each body's net force
	for (auto& b : m_bodies) {
		b->h_a = { 0, 0, 0 };
	}

	// sum up each body's net force
	for (const ForceGenerator* f : m_forces) {
		Body& b = *(f->B);
		b.h_a + f->value;
	}

	// update system h_a and mechanical energy
	m_sysState.e_m = 0.0;
	for (int i = 0; i < m_nB; i++) {

		const Body& b = *m_bodies.at(i);
		const Matrix h_a = b.h_a;
		
		// form system h_a from each body's net h_a
		int idx = 3 * i;
		for (int ii = idx; ii < idx + 2; ii++) {
			m_sysState.h_a(ii) = h_a(ii);
		}

		m_sysState.e_m += b.calcKineticEnergy();
		if (m_applyGravity) {
			m_sysState.e_m += b.mass * m_gravAcc * b.r.y; // PE = m*g*h
		}
	}

	// update system matrices from joints
	for (int i = 0; i < m_nJ; i++) {
		const Joint* j = m_joints.at(i);

		switch (j->getType())
		{
		case (Joint::rev): {
			const Revolute& rev = *(Revolute*)j;

			// calculate distance between points
			Point& Pi = *rev.Pi;
			Point& Pj = *rev.Pj;
			const Vec2d r_ji(Pj.rP - Pi.rP);
			const Vec2d v_ji(Pj.rP_dot - Pi.rP_dot);
			const Matrix f_d = m_sysState.k_c * r_ji - m_sysState.k_c_dot * v_ji;

			// update system drift force
			const int idx = 2 * i;
			for (int ii = idx; ii < idx+2; ii++) {
				m_sysState.f_d(ii) = f_d(ii);
			}

			// update system jacobians
			const int ciBegin = rev.coli;
			const int cjBegin = rev.colj;
			const int rBegin  = rev.row;
			const int ciEnd = ciBegin + rev.getNumConstraints();
			const int cjEnd = cjBegin + rev.getNumConstraints();
			const int rEnd  = rBegin  + rev.getNumConstraints(); // Will likely need to correct index

			unsigned int jr = 0;
			unsigned int jc = 0;

			//TODO: These are commented out because we're accessing out of bounds.
			// fix indexing

			if (Pi.isOnGnd()) {
				for (int r = rBegin; r < rEnd; r++) {
					for (int c = cjBegin; c < cjEnd; c++) {
						//m_sysState.J(r, c) = rev.Dj(jr, jc);
						//m_sysState.J_dot(r, c) = rev.Dj_dot(jr, jc);
						jr++;
					}
					jc++;
					jr = 0;
				}
			}
			else if (Pj.isOnGnd()) {
				for (int r = rBegin; r < rEnd; r++) {
					for (int c = ciBegin; c < ciEnd; c++) {
						//m_sysState.J(r, c) = rev.Di(jr, jc);
						//m_sysState.J_dot(r, c) = rev.Di_dot(jr, jc);
						jr++;
					}
					jc++;
					jr = 0;
				}
			}
			else {
				for (int r = rBegin; r < rEnd; r++) {
					for (int c = cjBegin; c < cjEnd; c++) {
						//m_sysState.J(r, c) = rev.Di(jr, jc);
						//m_sysState.J(r, c) = rev.Dj(jr, jc);
						//m_sysState.J_dot(r, c) = rev.Di_dot(jr, jc);
						//m_sysState.J_dot(r, c) = rev.Dj_dot(jr, jc);
						jr++;
					}
					jc++;
					jr = 0;
				}
			}
			break;
		}
		default:
			FATAL("Undefined joint type", -1);
		}
	}

	// integrate system

	// flow down system state to vectors
	updateBodies();
	updatePoints();
	updateJoints();
}

void Application::render()
{
	print("Application rendered");
	DGB_APP_CALL(m_renderCounter++);
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
	for (Point* p : m_points) {

		if (p->isOnGnd()) {
			continue;
		}

		auto& b = *p->B;
		p->sP = p->sP_local.rotate(b.phi);
		p->sP_dot = p->sP.rot90() * b.phi_dot;
		p->rP = b.r + p->sP;
		p->rP_dot = b.r_dot + p->sP_dot;
	}
}

void Application::updateJoints()
{
}
