#include "CuteAtom.h"
#include "CuteConfig.h"

#pragma once

typedef struct
{
	ctAtom *locals;
	uint32_t locals_count;
	uint32_t return_address;
} ctFuncFrame;

typedef struct
{
	ctFuncFrame frames[CUTE_FUNCSTACK_LIMIT];
	uint32_t count;
	uint32_t cap;
} ctFrameStack;