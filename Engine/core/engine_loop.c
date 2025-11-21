#include "CuteAtom.h"
#include "CuteByte.h"
#include "CuteEngine.h"
#include "../state/state.h"
#include "../state/exestack.h"
#include <stdio.h>





void CuteEngine_execLoop(CtState* state)
{
	ctInstrSize instr;

	ctInstrSize* instrs = state->img->instrs;
	Constant* consts = state->img->consts;

	CtAtom a1;
	CtAtom a2;

	uint64_t pt;

	CtAtom locals[10];

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
			CtExeStack_pop(&state->exestack);
			break;

        case instrLoadCoI32:
			a1.i32 = consts[instrs[state->pc++]].i32;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadCoI64:
			a1.i64 = consts[instrs[state->pc++]].i64;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadCoF32:
			a1.f32 = consts[instrs[state->pc++]].f32;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadCoF64:
			a1.f64 = consts[instrs[state->pc++]].f64;
			CtExeStack_push(&state->exestack, a1);
			break;
		
        case instrLoadI32:
			pt = instrs[state->pc++];
			a1.i32 = locals[pt].i32;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadI64:
			pt = instrs[state->pc++];
			a1.i64 = locals[pt].i64;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadF32:
			pt = instrs[state->pc++];
			a1.f32 = locals[pt].f32;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrLoadF64:
			pt = instrs[state->pc++];
			a1.f64 = locals[pt].f64;
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrStoreI32:
			pt = instrs[state->pc++];
			locals[pt] = CtExeStack_pop(&state->exestack);
			break;

        case instrStoreI64:
			pt = instrs[state->pc++];
			locals[pt] = CtExeStack_pop(&state->exestack);
			break;

        case instrStoreF32:
			pt = instrs[state->pc++];
			locals[pt] = CtExeStack_pop(&state->exestack);
			break;

        case instrStoreF64:
			pt = instrs[state->pc++];
			locals[pt] = CtExeStack_pop(&state->exestack);
			break;

        case instrAddI32:
			mCtBinaryOp(i32, a1, a2, +, &state->exestack);
			break;

        case instrAddI64:
			mCtBinaryOp(i64, a1, a2, +, &state->exestack);
			break;

        case instrAddF32:
			mCtBinaryOp(f32, a1, a2, +, &state->exestack);
			break;

        case instrAddF64:
			mCtBinaryOp(f64, a1, a2, +, &state->exestack);
			break;

        case instrSubI32:
			mCtBinaryOp(i32, a1, a2, -, &state->exestack);
			break;

        case instrSubI64:
			mCtBinaryOp(i64, a1, a2, -, &state->exestack);
			break;

        case instrSubF32:
			mCtBinaryOp(f32, a1, a2, -, &state->exestack);
			break;

        case instrSubF64:
			mCtBinaryOp(f64, a1, a2, -, &state->exestack);
			break;

        case instrMulI32:
			mCtBinaryOp(i32, a1, a2, *, &state->exestack);
			break;

        case instrMulI64:
			mCtBinaryOp(i64, a1, a2, *, &state->exestack);
			break;

        case instrMulF32:
			mCtBinaryOp(f32, a1, a2, *, &state->exestack);
			break;

        case instrMulF64:
			mCtBinaryOp(f64, a1, a2, *, &state->exestack);
			break;

        case instrDivI32:
			mCtBinaryOp(i32, a1, a2, /, &state->exestack);
			break;

        case instrDivI64:
			mCtBinaryOp(i64, a1, a2, /, &state->exestack);
			break;

        case instrDivF32:
			mCtBinaryOp(f32, a1, a2, /, &state->exestack);
			break;

        case instrDivF64:
			mCtBinaryOp(f64, a1, a2, /, &state->exestack);
			break;

        case instrCmpI32:
			mCtCmpOp(i32, a1, a2, &state->exestack);
			break;

        case instrCmpI64:
			mCtCmpOp(i64, a1, a2, &state->exestack);
			break;

        case instrCmpF32:
			mCtCmpOp(f32, a1, a2, &state->exestack);
			break;

        case instrCmpF64:
			mCtCmpOp(f64, a1, a2, &state->exestack);
			break;

        case instrCmp2BoolEq:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8 == 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolNe:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8 != 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolLt:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8 == -1) {a1.by8 = 1;} else {a1.by8 = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolLe:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8 <= 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolGt:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8 == 1) {a1.by8 = 1;} else {a1.by8 = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrCmp2BoolGe:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8 >= 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			CtExeStack_push(&state->exestack, a1);
			break;

        case instrJmp:
			pt = instrs[state->pc++];
			state->pc = pt;
			break;

        case instrJmpTrue:
			a1 = CtExeStack_pop(&state->exestack);
			if (!a1.by8) {state->pc++; continue;}
			pt = instrs[state->pc++];
			state->pc = pt;
			break;
		 
        case instrJmpFalse:
			a1 = CtExeStack_pop(&state->exestack);
			if (a1.by8) {state->pc++; continue;}
			pt = instrs[state->pc++];
			state->pc = pt;
			break;
		 
        case instrCall:
        case instrCallVirtual:
        case instrReturn:
        case instrNewCon:
        case instrAccessCon:
        case instrDelCon:
		case instrOutI32:
			a1 = *CtExeStack_peek(&state->exestack);
			printf("%d\n", a1.i32);
			break;

		case instrOutF32:
			a1 = *CtExeStack_peek(&state->exestack);
			printf("%f\n", a1.f32);
			break;

		case instrOutI64:
			a1 = *CtExeStack_peek(&state->exestack);
			printf("%ld\n", a1.i64);
			break;

		case instrOutF64:
			a1 = *CtExeStack_peek(&state->exestack);
			printf("%lf\n", a1.f64);
			break;
    }
	
	}

}

