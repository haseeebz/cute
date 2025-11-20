#include "CuteByte.h"
#include "CuteAtom.h"
#include "../state/state.h"

#pragma once 


#ifdef __cplusplus
extern "C" {
#endif

#define mCt32To64(varHigh, varLow, var64) \
var64 = ((uint64_t) varHigh << 32) | varLow;

#define mCt64To32(var64, varHigh, varLow) \
varLow = (uint64_t) var64 & 0xFFFFFFFF; \
varHigh = (uint64_t) var64 >> 32;


#define mCtBinaryOp32(type, var1, var2, op, stack) \
var2 = CtExeStack_pop(stack).type; \
var1 = CtExeStack_pop(stack).type; \
var1 = var1 op var2; \
CtExeStack_push(stack, (CtAtom) {.type = var1});


#define mCtBinaryOp64(type, var1, var2, var3, op, stack) \
var3 = CtExeStack_pop(&state->exestack).r; \
var2 = CtExeStack_pop(&state->exestack).r; \
mCt32To64(var2, var3, var3); \
\
var2 = CtExeStack_pop(&state->exestack).r; \
var1 = CtExeStack_pop(&state->exestack).r; \
mCt32To64(var1, var2, var2); \
\
var1 = var2 + var3; \
mCt64To32(var1, var2, var3); \
CtExeStack_push(&state->exestack, (CtAtom) {.type = var3}); \
CtExeStack_push(&state->exestack, (CtAtom) {.type = var2}); \




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