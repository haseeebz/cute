#include "CuteAtom.h"
#include "config.h"

#pragma once

typedef struct
{
	ctAtom* locals;
	uint32_t locals_count;
} ctFuncFrame;

typedef struct
{
	ctFuncFrame frames[FUNC_CALL_LIMIT];
	uint32_t count;
	uint32_t cap;
} ctFrameStack;