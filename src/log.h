#pragma once
#include <iostream>

#ifdef _DEBUG
namespace LOG
{
	constexpr auto RESET = "\033[0m";
	constexpr auto BLACK = "\033[30m";
	constexpr auto RED = "\033[31m";
	constexpr auto GREEN = "\033[32m";
	constexpr auto YELLOW = "\033[33m";
	constexpr auto BLUE = "\033[34m";
	constexpr auto MAGENTA = "\033[35m";
	constexpr auto CYAN = "\033[36m";
	constexpr auto WHITE = "\033[37m";
}

#define log(x)   std::cout << x << "\n";
#define highlight(x)  std::cout << LOG::GREEN  << x << LOG::RESET << "\n";
#define warn(x)  std::cout << LOG::YELLOW << "Warning: " << LOG::RESET << x << "\n";
#define error(x) std::cout << LOG::RED    << "Error: "   << LOG::RESET << x << "\n";

#else
#define log(x)
#define note(x)
#define warn(x)
#define error(x)    
#endif
