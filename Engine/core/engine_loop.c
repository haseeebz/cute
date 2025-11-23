#include "CuteAtom.h"
#include "CuteByte.h"
#include "CuteEngine.h"
#include "../state/state.h"
#include <stdio.h>





void CuteEngine_execLoop(ctState* state)
{
	ctInstrSize instr;

	ctInstrSize* instrs = state->img->instrs;
	ctProgramConstant* consts = state->img->consts;

	ctAtom a1;
	ctAtom a2;

	uint64_t pt;


	while (1)
	{

	if (state->error_encountered)
	{
		printf("%s: ", state->error.name);
		printf(" %s\n", state->error.msg);
		return;
	}

	instr = instrs[state->pc++];
	
	switch (instr) 
	{
        case instrHalt:
			return;

        case instrDupAtom:
			ctState_pushExeAtom(state, ctState_peekExeAtom(state));
			break;

        case instrPopAtom:
			ctState_popExeAtom(state);
			break;

        case instrLoadCoI32:
			a1.i32 = consts[instrs[state->pc++]].i32;
			ctState_pushExeAtom(state, a1);
			break;

        case instrLoadCoI64:
			a1.i64 = consts[instrs[state->pc++]].i64;
			ctState_pushExeAtom(state, a1);
			break;

        case instrLoadCoF32:
			a1.f32 = consts[instrs[state->pc++]].f32;
			ctState_pushExeAtom(state, a1);
			break;

        case instrLoadCoF64:
			a1.f64 = consts[instrs[state->pc++]].f64;
			ctState_pushExeAtom(state, a1);
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
			mCtBinaryOp(i32, a1, a2, +, state);
			break;

        case instrAddI64:
			mCtBinaryOp(i64, a1, a2, +, state);
			break;

        case instrAddF32:
			mCtBinaryOp(f32, a1, a2, +, state);
			break;

        case instrAddF64:
			mCtBinaryOp(f64, a1, a2, +, state);
			break;

        case instrSubI32:
			mCtBinaryOp(i32, a1, a2, -, state);
			break;

        case instrSubI64:
			mCtBinaryOp(i64, a1, a2, -, state);
			break;

        case instrSubF32:
			mCtBinaryOp(f32, a1, a2, -, state);
			break;

        case instrSubF64:
			mCtBinaryOp(f64, a1, a2, -, state);
			break;

        case instrMulI32:
			mCtBinaryOp(i32, a1, a2, *, state);
			break;

        case instrMulI64:
			mCtBinaryOp(i64, a1, a2, *, state);
			break;

        case instrMulF32:
			mCtBinaryOp(f32, a1, a2, *, state);
			break;

        case instrMulF64:
			mCtBinaryOp(f64, a1, a2, *, state);
			break;

        case instrDivI32:
			mCtBinaryOp(i32, a1, a2, /, state);
			break;

        case instrDivI64:
			mCtBinaryOp(i64, a1, a2, /, state);
			break;

        case instrDivF32:
			mCtBinaryOp(f32, a1, a2, /, state);
			break;

        case instrDivF64:
			mCtBinaryOp(f64, a1, a2, /, state);
			break;

        case instrCmpI32:
			mCtCmpOp(i32, a1, a2, state);
			break;

        case instrCmpI64:
			mCtCmpOp(i64, a1, a2, state);
			break;

        case instrCmpF32:
			mCtCmpOp(f32, a1, a2, state);
			break;

        case instrCmpF64:
			mCtCmpOp(f64, a1, a2, state);
			break;

        case instrCmp2BoolEq:
			a1 = ctState_popExeAtom(state);
			if (a1.by8 == 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			ctState_pushExeAtom(state, a1);
			break;

        case instrCmp2BoolNe:
			a1 = ctState_popExeAtom(state);
			if (a1.by8 != 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			ctState_pushExeAtom(state, a1);
			break;

        case instrCmp2BoolLt:
			a1 = ctState_popExeAtom(state);
			if (a1.by8 == -1) {a1.by8 = 1;} else {a1.by8 = 0;}
			ctState_pushExeAtom(state, a1);
			break;

        case instrCmp2BoolLe:
			a1 = ctState_popExeAtom(state);
			if (a1.by8 <= 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			ctState_pushExeAtom(state, a1);
			break;

        case instrCmp2BoolGt:
			a1 = ctState_popExeAtom(state);
			if (a1.by8 == 1) {a1.by8 = 1;} else {a1.by8 = 0;}
			ctState_pushExeAtom(state, a1);
			break;

        case instrCmp2BoolGe:
			a1 = ctState_popExeAtom(state);
			if (a1.by8 >= 0) {a1.by8 = 1;} else {a1.by8 = 0;}
			ctState_pushExeAtom(state, a1);
			break;

        case instrJmp:
			pt = instrs[state->pc++];
			state->pc = pt;
			break;

        case instrJmpTrue:
			a1 = ctState_popExeAtom(state);
			if (!a1.by8) {state->pc++; continue;}
			pt = instrs[state->pc++];
			state->pc = pt;
			break;
		 
        case instrJmpFalse:
			a1 = ctState_popExeAtom(state);
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
			a1 = ctState_peekExeAtom(state);
			printf("%d\n", a1.i32);
			break;

		case instrOutF32:
			a1 = ctState_peekExeAtom(state);
			printf("%f\n", a1.f32);
			break;

		case instrOutI64:
			a1 = ctState_peekExeAtom(state);
			printf("%ld\n", a1.i64);
			break;

		case instrOutF64:
			a1 = ctState_peekExeAtom(state);
			printf("%lf\n", a1.f64);
			break;
    }
	
	}

}

