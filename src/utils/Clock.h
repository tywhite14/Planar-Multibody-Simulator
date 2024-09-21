#pragma once

#include <chrono>

class Clock
{
public:
	Clock() : m_start(std::chrono::high_resolution_clock::now())
	{
	}

	inline double getSeconds() const {
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_start).count();
	}

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};
