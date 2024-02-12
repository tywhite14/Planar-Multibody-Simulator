#pragma once

#include <chrono>

struct Timer
{
public:
	float duration; // Time elapsed in us
	bool isRunning;

	Timer() : duration(0) {}

	void start(); // Start timer
	void stop(); // Stop timer
	void getElapsedTime();

private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point stopTime;
};
