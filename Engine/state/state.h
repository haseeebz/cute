#include "CuteAtom.h"

#include "CuteByte.h"
#include "error.h"
#include "exestack.h"
#include "frame.h"

#pragma once 

typedef struct
{
	uint64_t pc;

	ctProgramImage* img; // do not free

	ctFrameStack frame_stack;
	ctExeStack exestack;
	
	bool error_encountered;
	ctError error;
} ctState;


void ctState_init(ctState* state, ctProgramImage* img);
void ctState_end(ctState* state);

void ctState_pushExeAtom(ctState* state, ctAtom atom);
ctAtom ctState_popExeAtom(ctState* state);
ctAtom ctState_peekExeAtom(ctState* state);

void ctState_setupFuncFrame(ctState* state, uint32_t func_id);
void ctState_returnFuncFrame(ctState* state);

void ctState_setLocal(ctState* state, uint32_t pos, ctAtom* atom);
ctAtom ctState_getLocal(ctState* state, uint32_t pos);
void ctState_moveLocal(ctState* state, uint32_t src, uint32_t dest);
void ctState_copyLocal(ctState* state, uint32_t src, uint32_t dest);
