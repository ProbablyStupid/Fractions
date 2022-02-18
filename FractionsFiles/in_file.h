#pragma once

#include <iostream>

#include "fstd.h"
#include "ffutility.h"

class in_file
{
private:
	std::string m_filepath;

	bool m_loaded = false;
	std::string m_file_contents;

public:
	in_file() = default;

	// automatically loads the file
	in_file(std::string filepath);

	// true = load, false = don't load
	in_file(std::string filepath, bool auto_load);

	void set_filepath(std::string filepath);
	void load();

	// i.e. trusted load -> does not perform any checks
	// + does not report any errors
	void tload();

	// also deletes m_file_contents
	std::string* get_contents();

	// flushes m_file_contents
	void flush();

	[[nodiscard]] bool does_exist() const
	{
		return file_exists(this->m_filepath);
	}
};
