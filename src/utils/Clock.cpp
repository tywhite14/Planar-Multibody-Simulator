#include "Clock.h"
#include "log.h"

Clock::Clock() : _start(std::chrono::high_resolution_clock::now())
{
}

double Clock::restart()
{
	double t = getSeconds();
	_start = std::chrono::high_resolution_clock::now();
	return t;
}


double SystemClock::restart()
{
	FATAL("You're attempting to restart the system clock. -100 aura.", -100);
}

SystemClock sysClock;
