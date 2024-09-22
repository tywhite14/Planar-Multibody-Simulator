#include "Joint.h"
#include "log.h"

Joint::Joint(Type type) :
	m_type(type),
	m_nConsts(0),
	m_nBodies(0),
	row(-1),
	coli(-1),
	colj(-1)
{
	Debug("Joint created");
}

Joint::Joint(const Joint& j)
{
	*this = j;
	Debug("Joint copied");
}

Joint::~Joint()
{
	Debug("Joint destroyed");
}

Revolute::Revolute(Point* pi, Point* pj) :
	Joint(rev),
	Pi(pi),
	Pj(pj)
{
	m_nConsts = 2;
	m_nBodies = 2;
	Di     = Matrix::zeros(m_nConsts, 3);
	Dj     = Matrix::zeros(m_nConsts, 3);
	Di_dot = Matrix::zeros(m_nConsts, 3);
	Dj_dot = Matrix::zeros(m_nConsts, 3);

	Debug("Revolute joint created");
}

void Revolute::updateJacobians()
{
	const Vec2d& vi = Pi->sP.rot90();
	const Vec2d& vj = Pj->sP.rot90();
	const Body* Bi = Pi->B;
	const Body* Bj = Pj->B;

	if (Pi->isOnGnd()) {
		const Vec2d& b = Pj->sP * Bj->phi_dot;

		Dj = { -1, 0, -vj.x, 0, -1, -vj.y };
		Dj_dot = { 0, 0, b.x, 0, 0, b.y };
	}
	else if (Pj->isOnGnd()) {
		const Vec2d& b = Pi->sP * Bi->phi_dot;

		Di = { -1, 0, -vi.x, 0, -1, -vi.y };
		Di_dot = { 0, 0, b.x, 0, 0, b.y };
	}
	else {
		const Vec2d& bi = Pi->sP * Bi->phi_dot;
		const Vec2d& bj = Pj->sP * Bj->phi_dot;

		Di = { -1, 0, -vi.x, 0, -1, -vi.y };
		Dj = { -1, 0, -vj.x, 0, -1, -vj.y };
		Di_dot = { 0, 0, bi.x, 0, 0, bi.y };
		Dj_dot = { 0, 0, bj.x, 0, 0, bj.y };
	}
}
