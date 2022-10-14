#pragma once

#include <string>
#include <filesystem>

// this is kept as a standard function to be future proof
// May seem obsolete and is quite silly
inline bool file_exists(const std::string& filepath)
{
	// TODO: add to debug macro / build macro
	std::cout << "Checking for a file in directory : " <<
		std::filesystem::current_path() << std::endl;
	//std::filesystem::path f = filepath;
	return std::filesystem::exists(filepath);
}
