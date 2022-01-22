#pragma once

#include <iostream>
#include "../FractionsCore/FractionsCore.h"

typedef std::pair<unsigned, unsigned> dimensions;

class FractionsInstance
{
private:
	fractions_core_context context;
public:

	FractionsInstance() = default;
	~FractionsInstance() = default;

	void set_window_dimensions(dimensions);
	void set_window_title(std::string& title);
	void set_window_resizable(bool);

	void create_window();
};