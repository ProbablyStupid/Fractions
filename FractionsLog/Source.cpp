#include "FractionsLog.h"

outstream fout = outstream();

void outstream::operator<<(const char* _l)
{
	this->log << _l;
	this->lines++;
	printf(_l);
	printf("\n");
}

void outstream::out(const char* _l)
{
	this->log << _l;
	this->lines++;
	printf(_l);
	printf("\n");
}

outstream::outstream()
{
	this->out("initialized oustream");
}