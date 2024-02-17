#pragma once

#include <chrono>

class Clock
{
public:
	Clock();

	void restart();
	double getElapsedTime();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<double> duration;
};
