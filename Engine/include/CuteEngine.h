#include "CuteByte.h"
#include "../state/state.h"

#pragma once 


#ifdef __cplusplus
extern "C" {
#endif


#define mCtBinaryOp(type, var1, var2, op, state) \
var2 = ctState_popExeAtom(state); \
var1 = ctState_popExeAtom(state); \
var1.type = var1.type op var2.type; \
ctState_pushExeAtom(state,var1);

#define mCtCmpOp(type, var1, var2, state) \
var2 = ctState_popExeAtom(state); \
var1 = ctState_popExeAtom(state); \
if (var1.type > var2.type) {var1.by8 = 1;} \
else if (var1.type < var2.type) {var1.by8 = -1;} \
else {var1.by8 = 0;} \
ctState_pushExeAtom(state, var1);


typedef struct
{
	ctProgramImage img;
} CuteEngine;

extern CuteEngine ctEngine;


void CuteEngine_init();
void CuteEngine_end();

void CuteEngine_loadImage(char *filepath);

void CuteEngine_execLoop(ctState *state);

void CuteEngine_runMain(); // main entry point





#ifdef __cplusplus
}
#endif