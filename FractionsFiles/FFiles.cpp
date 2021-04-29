#include "FFiles.h"

#include <sstream>
#include <filesystem>

namespace ff
{
	/*
	void file_queue::append(std::pair<std::string, bool> file)
	{
		this->filenames_in_order.push(file);
		this->changed_compiled_get = true;
	}

	_NODISCARD std::string* file_queue::get(char seperator)
	{

		std::stack<std::pair<std::string, bool>> myStack = this->filenames_in_order;

		if (changed_compiled_get) {
			std::stringstream stream;

			for (int i = 0; i < myStack.size(); i++)
			{
				stream << myStack.top().first << " -> is binary: " <<
					(myStack.top().second ? "true" : "false") << seperator;
				myStack.pop();
			}

			std::string *b = new std::string;
			b->assign(stream.str());
			this->compiled_get = b;
			this->changed_compiled_get = false;
		}

		return this->compiled_get;
	}

	void file_queue::read()
	{
		if (this->filenames_in_order.top().second)
		{
			std::ifstream myFile(this->filenames_in_order.top().first, std::ios::in | std::ios::binary |
				std::ios::ate);
			const auto size = std::filesystem::file_size(this->filenames_in_order.top().first);
			unsigned char* myChars = (unsigned char*) malloc(sizeof(unsigned char) * size);
			
		}
		else
		{

		}
		this->filenames_in_order.pop();
	}
	*/

	_NODISCARD std::string _FF binary_loader::__next()
	{
		std::string myString;
		myString = this->files.top();
		this->files.pop();
		return myString;
	}

	void binary_loader::__blind()
	{
		free(this->blind);
		this->blind = new binary_file_content;
	}

	void binary_loader::__cBlind()
	{
		if (this->blind != NULL)
			throw std::runtime_error("FF error - blind reading unsuccessful");
	}

	void binary_loader::__add_blind()
	{
		this->read_files.push_back(NULL);
	}

	void binary_loader::__read_blind(std::string filepath)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
		auto end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		auto size = std::size_t(end - stream.tellg());
		std::vector<std::byte> content(size);
		if (!stream.read((char*)content.data(), content.size()))
			throw std::runtime_error("failed reading binary files : " + filepath);
		__cBlind();
		// check this
		this->blind->data = content;
	}

	void binary_loader::__blind_push(std::string filepath)
	{
		this->blind->file_name = filepath;
		this->read_files[this->read_files.size()] = this->blind;
	}

	void binary_loader::operator<< (std::string _i)
	{
		this->files.push(_i);
	}

	void binary_loader::operator>> (_FF binary_file_content* val)
	{
		std::string myString = this->__next();
		this->__blind();
		this->__read_blind(myString);
		val = std::move(this->blind);
	}

	void _FF binary_loader::operator= (std::string val)
	{
		this->files.push(val);
	}

	void binary_loader::read_next()
	{
		this->__add_blind();
		std::string myString = this->__next();
		this->__blind();
		this->__read_blind(myString);
		this->__blind_push(myString);
	}

	void _FF binary_loader::read_all()
	{
		for (int i = 0; i < this->files.size(); i++)
			this->read_next();
	}
}