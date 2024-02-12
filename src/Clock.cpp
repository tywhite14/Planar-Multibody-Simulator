#include <iostream>

#include "Clock.h"

Clock::Clock() : duration(0.0)
{
	start = std::chrono::high_resolution_clock::now();
}

void Clock::restart()
{
	start = std::chrono::high_resolution_clock::now();
}

double Clock::getElapsedTime()
{
	duration = std::chrono::high_resolution_clock::now() - start;
	return duration.count();
}
