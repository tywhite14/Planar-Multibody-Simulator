#include <iostream>

#include "Timer.h"

void Timer::start()
{
	startTime = std::chrono::high_resolution_clock::now();
	isRunning = true;
}

void Timer::stop()
{
	stopTime = std::chrono::high_resolution_clock::now();
	duration = (stopTime - startTime).count() * 0.001f;
	isRunning = false;
}

void Timer::getElapsedTime()
{
	std::cout << "Timer took " << duration << " us" << std::endl;
}
