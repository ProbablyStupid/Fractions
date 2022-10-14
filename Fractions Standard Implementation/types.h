#pragma once

#include <iostream>

// boolean
#ifndef _INT_BOOLEAN_PRESENT
#ifndef FAST_BOOLEAN

enum boolean
{
	False = 0, True = 1, Undefined = 2
};

#endif
#endif

#ifndef _INT_BOOLEAN_PRESENT

// Standard macro for saying `boolean::Undefined`
#define undef boolean::Undefined
// Standard macro for turning a boolean into a bool
// given that it's not undefined
#define Bool(x) (x == boolean::True ? true : false)
// Standard macro for checking whether a boolean is undefined
#define bcheck(x) (x == undef ? true : false)
// Standard macro for checking if a boolean is undefined
// with custom procedure
#define BCheck(x, y) if (x == undef) y();

#endif

#ifdef FAST_BOOLEAN
#ifndef _INT_BOOLEAN_PRESENT

using boolean = unsigned char;

#define False 0
#define True 1
#define Undefined 2
#define undef 2

// TODO Verify that this madness works
inline bool _bool (boolean x)
{
	return (bool)x;
}

#endif
#endif

// simple types

using dimension			= std::pair<unsigned, unsigned>;
using uuid				= uint64_t;
using function_pointer	= void(*)();