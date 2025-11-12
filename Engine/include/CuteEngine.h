#include "CuteByte.h"
#include "CuteAtom.h"
#include "../context/context.h"

#pragma once 


#ifdef __cplusplus
extern "C" {
#endif

#define BasicBinaryOp(atom1, atom2, type, op, stack) \
atom2 = ctExeStack_pop(stack); \
atom1 = ctExeStack_pop(stack); \
atom1.type = atom1.type op atom2.type; \
ctExeStack_push(stack, atom1);




typedef struct
{
	ctProgramImage img;
} CuteEngine;

extern CuteEngine ctEngine;


void CuteEngine_init();
void CuteEngine_end();
void CuteEngine_loadImage(char* filepath);

CtContext* CuteEngine_newContext();
void CuteEngine_endContext(CtContext** ctx);

void CuteEngine_runMain();
void CuteEngine_execLoop(CtContext* ctx);






#ifdef __cplusplus
}
#endif