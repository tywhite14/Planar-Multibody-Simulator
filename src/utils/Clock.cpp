#include "Clock.h"
#include "log.h"

Clock::Clock() : _start(std::chrono::high_resolution_clock::now())
{
}

void Clock::restart()
{
	_start = std::chrono::high_resolution_clock::now();
}

double Clock::getSecondsDecimal() const
{
	return static_cast<double>((std::chrono::high_resolution_clock::now() - _start).count()) / 1'000'000'000.0;
}

long long Clock::getSeconds() const
{
	// integer division
	return (std::chrono::high_resolution_clock::now() - _start).count() / 1'000'000'000;
}

long long Clock::getMillis() const
{
	// integer division
	return (std::chrono::high_resolution_clock::now() - _start).count() / 1'000'000;
}

long long Clock::getMicros() const
{
	// integer division
	return (std::chrono::high_resolution_clock::now() - _start).count() / 1000;
}

long long Clock::getNanos() const
{
	return (std::chrono::high_resolution_clock::now() - _start).count();
}


void SystemClock::restart()
{
	Error("You're attempting to restart the system clock. -100 aura.");
}

SystemClock sysClock;
