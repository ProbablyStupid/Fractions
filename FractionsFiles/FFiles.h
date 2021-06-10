// This is still a WIP

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include <lodepng.h>

#define _FF ff::

namespace ff {

	typedef struct text_file_content
	{
		unsigned char* data;
		unsigned long long int size;
		std::string file_name;
	} file_content;

	typedef struct binary_file_content
	{
		std::vector<std::byte> data;
		std::string file_name;
	} binary_file_content;

	// both are queues
	class binary_loader
	{
	public:

		void operator << (std::string);
		void operator >> (binary_file_content*);
		void operator = (std::string);

		void read_next();
		void read_all();
		/* equally devides loads - no regards of file size */
		void read_in_threads(uint8_t);

		void __add_blind();
		void __read_blind(std::string);
		void __blind_push(std::string);
		void __blind();
		void __cBlind();

		_NODISCARD std::string __next();

	private:


		binary_file_content* blind;

		std::stack<std::string> files;
		std::vector<binary_file_content*> read_files;
	};

	class text_loader
	{
	public:

	private:
	};
	//

	typedef struct PNG_data
	{
		std::vector<unsigned char> tex;
		unsigned witdh, height;
	} PNG_data;

	PNG_data* read_PNG(std::string filename);
}