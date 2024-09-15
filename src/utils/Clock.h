#pragma once

#include <chrono>

class Clock
{
public:
	Clock();

	void restart();
	double getSecondsDecimal() const;
	long long getSeconds() const;
	long long getMillis() const;
	long long getMicros() const;
	long long getNanos() const;

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

class SystemClock : public Clock
{
	void restart();
};
