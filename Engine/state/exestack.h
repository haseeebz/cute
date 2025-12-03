#include "CuteAtom.h"
#include "CuteConfig.h"

#pragma once


typedef struct
{
	ctAtom atoms[CUTE_EXESTACK_LIMIT];
	uint32_t count;
	uint32_t cap;
} ctExeStack;