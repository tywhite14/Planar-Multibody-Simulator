#include <cassert>

#include "utils/log.h"
#include "utils/Matrix.h"
#include "sim/System.h"
#include "utils/Clock.h"
#include "../models/demo.h"

int main()
{
	using namespace std;
	
	System* sim = new System;

	while(sim->isRunning)
		sim->update();

	return 0;
}
