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

	debug("Size of Sim: " << sizeof(sim));

	return 0;
}
