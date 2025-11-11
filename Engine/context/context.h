#include "CuteAtom.h"
#include "CuteByte.h"
#include "exestack.h"

#pragma once


typedef struct
{
	ctExeStack exestack;
	size_t pc;
	ctProgramImage* img;

	int64_t i1;
	int64_t i2;

	double f1;
	double f2;
	
} CtContext;

