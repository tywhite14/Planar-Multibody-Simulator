#pragma once

#include <vector>

#include "constants.h"
#include "Point.h"
#include "Vect2d.h"

struct Point;
struct Force;

class Body
{
public:
	Body();
	Body(
		double massIn,
		double MoiIn,
		Vect2d rIn,
		Vect2d r_dotIn,
		double phiIn,
		double phi_dotIn,
		anim::shape shapeIn
	);

	Body(const Body& b);
	~Body();

	void initialize();
	void update();

	inline float getAnimHeight() const;
	inline float getAnimWidth() const;
	inline float getAnimRadius() const;
	inline void setAnimHeight(const float sizeIn);
	inline void setAnimWidth(const float sizeIn);
	inline void setAnimRadius(const float sizeIn);

	// physical properties
	double mass;
	double Moi;

	// state
	Vect2d r;
	Vect2d r_dot;
	double phi;
	double phi_dot;
	Vect2d netAppliedForce;
	Vect2d netAppliedTorque;

	std::vector<Point> points;
	unsigned int sysIndex;

	// animation
	anim::shape shape;
	float animHeight;
	float animWidth;
	float animRadius;

private:
	Vect2d r_ddot;
	double phi_ddot;
};
