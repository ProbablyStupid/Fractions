// FractionsFiles uses the C++ IOS / standard to handle files
// future versions may use the C standard to handle files for
// improved speed
#pragma once

#include <fstream>
#include <sstream>
#include <vector>

struct fileContext
{
	std::string file_name;
	std::stringstream pre_file_write_buffer;
	std::fstream file;
};

void setCurrentFileContext(fileContext*);
void flushCurrentFileContext();

void setName(std::string);

void usePreFileWriteBuffer(bool);

void append(const char*);

// only used when PreFileWriteBuffers are used
void out();

// IN

const char* getFile(const char*);

// Fractions Files

// IN

struct FractionsFormatClass
{
	const char** values;
	FractionsFormatClass* subclasses;
};

class FractionsFormat
{
public:
	void setFFname(const char*);
	void setName(const char*);
	void appendClass(const char*);
	void vacateClass();
	void addInfo(const char*);
	void preWrite(); // will trigger a write
	void close(); // will write all the info to the file and close it
private:
	std::string filename;
	std::vector<FractionsFormatClass> classes;
};

// OUT

void openFractionsFormat(const char*);
void setClass(const char*);
void vacateClass(); // goes one class up
const char** getCurrentInfo();
void closeFractionsFormat();

// OBJ files

struct vec
{	};

struct vec3 : public vec
{
	long long int x, y, z;
};

struct vec4 : public vec
{
	long long int x, y, z, w;
};

void openOBJ(const char*);

void enumerateVerticies(unsigned int, std::vector<vec>);

void closeOBJ();
