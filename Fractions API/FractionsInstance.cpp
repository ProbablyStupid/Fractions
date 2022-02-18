#include "FractionsInstance.h"
#include "boolean.h"

typedef FractionsInstance sn;

#define con this->context

void sn::set_window_dimensions(dimensions d)
{
	con.window_dimension = d;
}

void sn::set_window_title(std::string& title)
{
	con.window_title = title.c_str();
}

void sn::set_window_resizable(bool x)
{
	con.window_resizable;
}

void sn::create_window()
{
}