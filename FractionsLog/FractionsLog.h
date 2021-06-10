#pragma once

#include <iostream>
#include <sstream>

// perhaps add options for colors and effects

class outstream
{
public:

	outstream();

	void operator << (const char*);
	void out(const char*);

private:
	std::stringstream log;
	unsigned int lines = 0;
};

extern outstream fout;

