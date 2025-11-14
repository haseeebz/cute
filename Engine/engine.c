#include "CuteAtom.h"
#include "CuteByte.h"
#include "CuteEngine.h"
#include "state/state.h"
#include "state/exestack.h"
#include <stdio.h>
#include <stdlib.h>


CuteEngine ctEngine;

void CuteEngine_init()
{
	return;
}


void CuteEngine_end()
{
	exit(EXIT_SUCCESS);
}


void CuteEngine_loadImage(char* filepath)
{
	ctImageError code = ctProgramImage_read(&ctEngine.img, filepath);

	if (code != ctImageError_Success)
	{
		if (code == ctImageError_ByteReadFailure)
		{
			printf("Image file could be not be read: %s\n", filepath);
			CuteEngine_end();
		}
		else if (code == ctImageError_FileNotFound)
		{
			printf("Image file not found: %s\n", filepath);
			CuteEngine_end();
		}
	}
}


void CuteEngine_runMain()
{
	CtState state;
	CtState_init(&state, &ctEngine.img);
	
	CuteEngine_execLoop(&state);

	CtState_end(&state);

	CuteEngine_end();
}


void CuteEngine_execLoop(CtState* state)
{
	ctInstrSize instr;

	ctInstrSize* instrs = state->img->instrs;
	Constant* consts = state->img->consts;

	CtAtom a1;
	CtAtom a2;

	while (1)
	{

	instr = instrs[state->pc++];

	switch (instr) 
	{
        case instrHalt:
			return;

        case instrDupAtom:
			CtExeStack_push(&state->exestack, *CtExeStack_peek(&state->exestack));
			break;

        case instrPopAtom:
			break;

        case instrLoadCoI8:
			break;

        case instrLoadCoI32:
			a1.i = consts[instrs[state->pc++]].i32;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadCoI64:
			break;

        case instrLoadCoF32:
			a1.f = consts[instrs[state->pc++]].f32;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadCoF64:
			break;
		
        case instrLoadI32:
			break;

        case instrLoadI64:
			break;

        case instrLoadF32:
			break;

        case instrLoadF64:
			break;

        case instrStoreI32:
			break;

        case instrStoreI64:
			break;

        case instrStoreF32:
			break;

        case instrStoreF64:
			break;

        case instrAddI32:
			mCtBinaryOp(a1, a2, i, +, &state->exestack);
			break;

        case instrAddI64:
			break;

        case instrAddF32:
			mCtBinaryOp(a1, a2, f, +, &state->exestack);
			break;

        case instrAddF64:
			break;

        case instrSubI32:
			mCtBinaryOp(a1, a2, i, -, &state->exestack);
			break;

        case instrSubI64:
			break;

        case instrSubF32:
			mCtBinaryOp(a1, a2, f, -, &state->exestack);
			break;

        case instrSubF64:
			break;

        case instrMulI32:
			mCtBinaryOp(a1, a2, i, *, &state->exestack);
			break;

        case instrMulI64:
			break;

        case instrMulF32:
			mCtBinaryOp(a1, a2, f, *, &state->exestack);
			break;

        case instrMulF64:
			break;

        case instrDivI32:
			mCtBinaryOp(a1, a2, i, /, &state->exestack);
			break;

        case instrDivI64:
			break;

        case instrDivF32:
			mCtBinaryOp(a1, a2, f, /, &state->exestack);
			break;

        case instrDivF64:
			break;

        case instrAnd:
			mCtBinaryOp(a1, a2, by, &&, &state->exestack);
			break;

        case instrOr:
			a2 = CtExeStack_pop(&state->exestack);
			a1 = CtExeStack_pop(&state->exestack);
			a1.by = a1.by || a2.by;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrNot:
			a1 = CtExeStack_pop(&state->exestack);
			a1.i = !a1.i;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrXor:
			break;

        case instrCmpI32:
			a2 = CtExeStack_pop(&state->exestack);
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.i < a2.i) {a1.by = -1;}
			else if (a1.i > a2.i) {a1.by = 1;}
			else  {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmpI64:
        case instrCmpF32:
			a2 = CtExeStack_pop(&state->exestack);
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.f < a2.f) {a1.by = -1;}
			else if (a1.f > a2.f) {a1.by = 1;}
			else  {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmpF64:

        case instrCmp2BoolEq:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by == 0) {a1.by = 1;} else {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolNe:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by != 0) {a1.by = 1;} else {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolLt:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by == -1) {a1.by = 1;} else {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolLe:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by <= 0) {a1.by = 1;} else {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolGt:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by == 1) {a1.by = 1;} else {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolGe:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by >= 0) {a1.by = 1;} else {a1.by = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrJmp:
			a1.i = instrs[state->pc++];
			state->pc = a1.i; 
			break;

        case instrJmpTrue:
			a1 = CtExeStack_pop(&state->exestack);
			if (!a1.by) {continue;} 
			a1.i = instrs[state->pc++];
			state->pc = a1.i; 
			break;

        case instrJmpFalse:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by) {continue;} 
			a1.i = instrs[state->pc++];
			state->pc = a1.i; 
			break;

        case instrCall:
        case instrCallVirtual:
        case instrReturn:
        case instrNewCon:
        case instrAccessCon:
        case instrDelCon:
		case instrOutI32:
			a1 = *CtExeStack_peek(&state->exestack);
			printf("%d\n", a1.i);
			break;

		case instrOutF32:
			a1 = *CtExeStack_peek(&state->exestack);
			printf("%f\n", a1.f);
			break;
    }
	
	}

}

