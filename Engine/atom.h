#pragma once 
#include <stdint.h>


typedef struct
{
	enum { atomInt, atomFloat } type; 
	union {
		int32_t i;
		float f;
	} val;
} Atom;

