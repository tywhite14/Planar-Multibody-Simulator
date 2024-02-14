#include <cassert>
#include "log.h"
#include "Matrix.h"
#include "Sim.h"
#include "Clock.h"
#include "../models/demo.h"

int main()
{
	using namespace std;
	
	Sim sim;
	sim.update();

	log("sim "    << sizeof(sim) << " bytes");
	log("bodies " << sizeof(sim.bodies) << " bytes");
	log("joints " << sizeof(sim.joints) << " bytes");
	
	return 0;
}
