#pragma once

#ifndef WINDOWS

#define NEW_LINE_CHAR (char) 0xA // i.e. '\n'

#else
#ifdef WINDOWS

#define NEW_LINE_CHAR (char) '\r\n'

#endif
#endif

#include <iostream>
#include <sstream>

void log	(std::string y_string); // time stamp + raw print
void warn	(std::string y_string); // time stamp + yellow text
void err	(std::string y_string); // time stamp + red text
void fatal	(std::string y_string); // time stamp + bold and highlighted red text
void print	(std::string y_string); // raw print
