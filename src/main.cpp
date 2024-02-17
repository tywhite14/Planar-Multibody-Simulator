#include <cassert>

#include "utils/log.h"
#include "utils/Matrix.h"
#include "sim/Sim.h"
#include "utils/Clock.h"
#include "../models/demo.h"

int main()
{
	using namespace std;
	
	Sim sim;

	while(sim.isRunning)
		sim.update();

	debug("Size of Sim: " << sizeof(sim));

	return 0;
}
