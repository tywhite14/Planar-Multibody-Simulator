#pragma once

#include <chrono>

class Clock
{
public:
	Clock();

	double restart();
	inline double getSeconds() const {
		return static_cast<double>((std::chrono::high_resolution_clock::now() - _start).count()) / 1'000'000'000.0;
	}

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

class SystemClock : public Clock
{
	double restart();
};
