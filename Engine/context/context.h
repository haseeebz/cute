#include "CuteAtom.h"
#include "CuteByte.h"
#include "exestack.h"

#pragma once


typedef struct
{
	ctExeStack exestack;
	size_t pc;
	ctProgramImage* img;
	
} CtContext;

