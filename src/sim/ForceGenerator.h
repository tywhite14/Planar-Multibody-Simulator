#pragma once

#include "Body.h"
#include "Point.h"
#include "Vector.h"

class ForceGenerator
{
public:
	ForceGenerator(Point* p = nullptr);
	ForceGenerator(const ForceGenerator& f);
	~ForceGenerator();

	inline bool isPointDefined() const { return P != nullptr; }
	inline bool isBodyDefined()  const { return B != nullptr; }
	Point* P;
	Body* B;
	Vec3d value;

private:
};
