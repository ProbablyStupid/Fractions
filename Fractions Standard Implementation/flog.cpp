#include <chrono>
#include <ctime>

#include "output.h"

static std::stringstream myLog;

void log(std::string y_string)
{
	std::time_t now;
	std::time(&now);
	myLog << '[' << std::to_string(now) << ']\t' << y_string << NEW_LINE_CHAR;
	std::cout << '[' << std::to_string(now)  << "]\t" << y_string << std::endl;
}

void warn(std::string y_string)
{
	std::time_t now;
	std::time(&now);
	myLog << "[WARNING]: " << '[' << std::to_string(now) << ']\t' << y_string << NEW_LINE_CHAR;
	std::cout << "\u001b[33m" << "[WARNING]: " << '[' << std::to_string(now) << "]\t" << y_string << "\u001b[0m" << std::endl;
}

void err(std::string y_string)
{
	std::time_t now;
	std::time(&now);
	myLog << "[ERROR]: " << '[' << std::to_string(now) << ']\t' << y_string << NEW_LINE_CHAR;
	std::cout << "\u001b[31m" << "[ERROR]: " << '[' << std::to_string(now) << "]\t" << y_string << "\u001b[0m" << std::endl;
}

void fatal(std::string y_string)
{
	std::time_t now;
	std::time(&now);
	myLog << "[FATAL ERROR]: " << '[' << std::to_string(now) << ']\t' << y_string << NEW_LINE_CHAR;
	std::cout << "\u001b[45m\u001b[1m" << "[FATAL ERROR]: " << '[' << std::to_string(now) << "]\t" << y_string << "\u001b[0m" << std::endl;
}

void print(std::string y_string)
{
	myLog << y_string << NEW_LINE_CHAR;
	std::cout << y_string << std::endl;
}