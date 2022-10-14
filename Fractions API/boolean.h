#pragma once

#ifndef FRACTIONS_CORE

#define _INT_BOOLEAN_PRESENT

enum boolean
{
	False = 0, True = 1, Undefined = 2
};

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