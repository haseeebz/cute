#include "CuteByte.h"
#include "CuteAtom.h"
#include "../state/state.h"

#pragma once 


#ifdef __cplusplus
extern "C" {
#endif


#define mCtBinaryOp(type, var1, var2, op, stack) \
var2 = CtExeStack_pop(stack); \
var1 = CtExeStack_pop(stack); \
var1.type = var1.type op var2.type; \
CtExeStack_push(stack,var1);





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