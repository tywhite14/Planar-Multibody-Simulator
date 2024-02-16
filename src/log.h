#pragma once

#include <iostream>
#include <iomanip>

#include "Clock.h"

#ifdef _DEBUG

	namespace LOG
	{
		constexpr auto RESET   = "\x1b[0m";
		constexpr auto BLACK   = "\x1b[30m";
		constexpr auto RED     = "\x1b[31m";
		constexpr auto GREEN   = "\x1b[32m";
		constexpr auto YELLOW  = "\x1b[33m";
		constexpr auto BLUE    = "\x1b[34m";
		constexpr auto MAGENTA = "\x1b[35m";
		constexpr auto CYAN    = "\x1b[36m";
		constexpr auto WHITE   = "\x1b[37m";

		static Clock clock;
	}

	#define TIMESTAMP \
				"[" << \
				std::setw(6) << \
				std::fixed << \
				std::setprecision(4) << \
				LOG::clock.getElapsedTime() << \
				std::defaultfloat << "] "

	#define COLORED_OUTPUT
	
	#ifdef COLORED_OUTPUT
		#define debug(x)   std::cout << TIMESTAMP << x << "\n"
		#define note(x)  std::cout << TIMESTAMP << LOG::GREEN  << x << LOG::RESET << "\n"
		#define warn(x)  std::cout << TIMESTAMP << __LINE__ << ": " << LOG::YELLOW << "Warning: " << LOG::RESET << x << "\n"
		#define error(x) std::cout << TIMESTAMP << __LINE__ << ": " << LOG::RED    << "Error: "   << LOG::RESET << x << "\n"
	#else
		#define log(x)   std::cout << TIMESTAMP << x << "\n"
		#define note(x)  std::cout << TIMESTAMP << x << "\n"
		#define warn(x)  std::cout << TIMESTAMP << __LINE__ << ": " << "Warning: " << x << "\n"
		#define error(x) std::cout << TIMESTAMP << __LINE__ << ": " << "Error: "   << x << "\n"
#endif

#else
	#define log(x)
	#define note(x)
	#define warn(x)
	#define error(x)
#endif
