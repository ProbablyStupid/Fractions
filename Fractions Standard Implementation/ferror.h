#pragma once

#include <iostream>

inline void error(const char* message)
{
	std::cerr << message << std::endl;
	throw std::runtime_error(message);
}