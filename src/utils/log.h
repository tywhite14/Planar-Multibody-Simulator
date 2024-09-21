#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "Clock.h"

// not the best spot for the system clock 
// but this makes the compiler happy
extern SystemClock sysClock;

#ifdef _DEBUG

static std::string filenameFromPath(std::string strIn);

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

	static std::ostringstream logStream;
}
	#define TIMESTAMP \
				"[" << \
				std::setw(6) << \
				std::fixed << \
				std::setprecision(4) << \
				sysClock.getSeconds() << \
				std::defaultfloat << "] "

	//#define LOGFILE
	#ifdef  LOGFILE
		static std::ofstream logFile("log.txt");
		#define print(x) {\
			LOG::logStream.str("");\
			LOG::logStream.clear();\
			LOG::logStream << TIMESTAMP << x << "\n";\
			std::string logString = LOG::logStream.str();\
			std::cout << logString;\
			logFile << logString;\
		}

	#else
		#define print(x) std::cout << TIMESTAMP << x << "\n"
	#endif

	#define EXIT_ON_FATAL

	#define Debug(x)	print(LOG::GREEN  << "Debug: "   << LOG::RESET << x)
	#define Warn(x)		print(LOG::YELLOW << "Warning: " << LOG::RESET << filenameFromPath(__FILE__) << ": " << __LINE__ << ": " << x)
	#define Error(x)	print(LOG::RED    << "Error: "   << LOG::RESET << filenameFromPath(__FILE__) << ": " << __LINE__ << ": " << x)
	#ifdef EXIT_ON_FATAL
		#define FATAL(x, n) Error(x); exit(n)
	#else 
		#define FATAL(x, n) Error(x)
	#endif
#else
	#define Debug(x)
	#define print(x) std::cout << x << "\n"
	#define Warn(x)
	#define Error(x) std::cout << x << "\n"
	#define FATAL(x, n) Error(x)
#endif

static std::string filenameFromPath(std::string strIn)
{
	size_t found = strIn.find_last_of("/\\");
	if (found != std::string::npos) {
		return strIn.substr(found + 1);
	}

	// If no '/' or '\' found, return the original string
	Warn("Issue finding filename");
	return strIn;
}
