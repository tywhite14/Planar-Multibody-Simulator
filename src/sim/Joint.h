#pragma once

#include "Body.h"
#include "Point.h"
#include "Matrix.h"

class Joint
{
public:
	enum Type
	{
		none = 0,
		rev,
		tran,
		roll,
		rigid
	};

	Joint(Type type = none);
	Joint(const Joint& j);
	~Joint();

	virtual void updateJacobians() = 0;
	inline unsigned int getNumConstraints() const { return m_nConsts; }
	inline unsigned int getNumBodies() const { return m_nBodies; }
	inline Type getType() const { return m_type; }

	Matrix Di;		// Body i jacobian
	Matrix Dj;		// Body j jacobian
	Matrix Di_dot;	// Body i jac_dot
	Matrix Dj_dot;	// Body j jac_dot
	int row;		// row in System State matrix
	int coli;		// column of Di in State matrix
	int colj;		// column of Dj in State matrix

protected:
	Type m_type;
	unsigned int m_nConsts; // number of constraints
	unsigned int m_nBodies; // number of bodies involved
};

class Revolute : public Joint
{
public:
	Revolute(Point* pi = nullptr, Point* pj = nullptr);

	void updateJacobians() override;

	Point* Pi;
	Point* Pj;
};
