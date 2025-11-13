#include "CuteByte.h"
#include "CuteAtom.h"
#include "../state/state.h"

#pragma once 


#ifdef __cplusplus
extern "C" {
#endif

#define BasicBinaryOp(atom1, atom2, type, op, stack) \
atom2 = CtExeStack_pop(stack); \
atom1 = CtExeStack_pop(stack); \
atom1.type = atom1.type op atom2.type; \
CtExeStack_push(stack, atom1);




typedef struct
{
	ctProgramImage img;
} CuteEngine;

extern CuteEngine ctEngine;


void CuteEngine_init();
void CuteEngine_end();

void CuteEngine_loadImage(char* filepath);

void CuteEngine_execLoop(CtState* state);

void CuteEngine_runMain(); // main entry point





#ifdef __cplusplus
}
#endif