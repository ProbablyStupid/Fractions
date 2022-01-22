#include "FractionsInstance.h"

typedef FractionsInstance sn;

FractionsInstance::FractionsInstance()
{}
FractionsInstance::~FractionsInstance()
{
	end_fractions_core_context();
}

#define con this->context

void sn::set_window_dimensions(dimensions d)
{
	auto [width, height] = d;
	con.window_width = width;
	con.window_height = height;
}

void sn::set_window_title(std::string& title)
{
	con.window_title = title.c_str();
}

void sn::set_window_resizable(bool x)
{
	con.window_resizable = x;
}

void sn::create_window()
{
	supply_fractions_core_context(&con);
	set_fractions_core_context();
	fractions_core_context_make_window();
	fractions_core_context_make_engine();
}