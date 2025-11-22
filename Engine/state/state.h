#include "CuteAtom.h"
#include "CuteByte.h"
#include "exestack.h"

#pragma once


typedef struct
{
	CtExeStack exestack;
	size_t pc;
	ctProgramImage* img;
} CtState;


void CtState_init(CtState* state, ctProgramImage* img);
void CtState_end(CtState* state);

void CtState_funcCall(CtState* state, uint32_t func_id);