#include "in_file.h"

#include <fstream>
#include <filesystem>
#include <vector>
#include "fstd.h"
#include "ffutility.h"

in_file::in_file(std::string filepath)
	: m_filepath(std::move(filepath))
{
	load();
}

in_file::in_file(std::string filepath, bool auto_load)
	: m_filepath(std::move(filepath))
{
	if (auto_load)
		load();
}

void in_file::set_filepath(std::string filepath)
{
	this->m_filepath = std::move(filepath);
}

void in_file::flush()
{
	m_file_contents.erase(m_file_contents.begin(), m_file_contents.end());
}

void in_file::load()
{
	if (!file_exists(this->m_filepath))
	{
		std::cout << "tried to load file : " << m_filepath << std::endl;
		error("[ERROR]\t\tFile does not exist!");
	}

	const uintmax_t file_size = std::filesystem::file_size(this->m_filepath);

	std::ifstream my_stream(m_filepath);

	if (!my_stream.is_open())
		error("File didn't open!");

	std::vector<char> contents(file_size);

	my_stream.read(&contents[0], file_size);
	my_stream.close();

	if (contents[0] == 0)
		error("File contents is 0");

	this->m_file_contents.assign(&contents[0]);

	this->m_loaded = true;
}

void in_file::tload()
{
	const auto file_size = std::filesystem::file_size(this->m_filepath);

	std::ifstream my_stream(m_filepath);

	auto* contents = static_cast<char*>(malloc(file_size * sizeof(char)));
	my_stream.read(contents, file_size);

	my_stream.close();

	// We can ignore that it could be 0 as this is the trusted load
	this->m_file_contents.assign(contents);
	free(contents);

	this->m_loaded = true;
}

std::string* in_file::get_contents()
{
	return &this->m_file_contents;
}


