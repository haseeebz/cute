#include "CuteAtom.h"
#include "CuteByte.h"
#include "CuteEngine.h"
#include "../state/state.h"
#include <stdio.h>
#include <string.h>


static inline void extractInt32(ctInstrSize *instrs, int32_t *i)
{
	memcpy(i, instrs, sizeof(*i));
}

static inline void extractInt64(ctInstrSize *instrs, int64_t *i)
{
	memcpy(i, instrs, sizeof(*i));
}

static inline void extractFloat32(ctInstrSize *instrs, float *i)
{
	memcpy(i, instrs, sizeof(*i));
}

static inline void extractFloat64(ctInstrSize *instrs, double *i)
{
	memcpy(i, instrs, sizeof(*i));
}



void CuteEngine_execLoop(ctState *state)
{
	ctInstrSize instr;

	ctInstrSize *instrs = state->img->instrs;

	ctAtom a1;
	ctAtom a2;

	ctU64 ptu;
	ctU32 pts;
	ctI32 ptj;

	while (1)
	{

	if (!state->isRunning)
	{	
		if (!state->error_encountered) {return;}

		printf("%s :: ", state->error.name);
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
			extractInt32(&instrs[state->pc], &a1.i32);
			state->pc += 4;
			ctState_pushExeAtom(state, a1);
			break;

        case instrLoadCoI64:
			extractInt64(&instrs[state->pc], &a1.i64);
			state->pc += 8;
			ctState_pushExeAtom(state, a1);
			break;

        case instrLoadCoF32:
			extractFloat32(&instrs[state->pc], &a1.f32);
			state->pc += 4;
			ctState_pushExeAtom(state, a1);
			break;

        case instrLoadCoF64:
			extractFloat64(&instrs[state->pc], &a1.f64);
			state->pc += 8;
			ctState_pushExeAtom(state, a1);
			break;
		
        case instrLoadI32:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_pushExeAtom(state, ctState_getLocal(state, pts));
			break;

        case instrLoadI64:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_pushExeAtom(state, ctState_getLocal(state, pts));
			break;

        case instrLoadF32:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_pushExeAtom(state, ctState_getLocal(state, pts));
			break;

        case instrLoadF64:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_pushExeAtom(state, ctState_getLocal(state, pts));
			break;

        case instrStoreI32:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_setLocal(state, pts, ctState_popExeAtom(state));
			break;

        case instrStoreI64:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_setLocal(state, pts, ctState_popExeAtom(state));
			break;

        case instrStoreF32:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_setLocal(state, pts, ctState_popExeAtom(state));
			break;

        case instrStoreF64:
			extractInt32(&instrs[state->pc], (int32_t*)&pts);
			state->pc += 4;
			ctState_setLocal(state, pts, ctState_popExeAtom(state));
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

		case instrDivU32:
			mCtBinaryOp(u32, a1, a2, /, state);
			break;

        case instrDivU64:
			mCtBinaryOp(u64, a1, a2, /, state);
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

		case instrJmpA:
			extractInt64(&instrs[state->pc], (int64_t*) &ptu);
			state->pc = ptu;
			break;

        case instrJmp:
			extractInt32(&instrs[state->pc], &ptj);
			state->pc += ptj;
			break;

        case instrJmpTrue:
			a1 = ctState_popExeAtom(state);
			if (!a1.by8) {state->pc += 4; continue;}
			extractInt32(&instrs[state->pc], &ptj);
			state->pc += ptj;
			break;
		 
        case instrJmpFalse:
			a1 = ctState_popExeAtom(state);
			if (a1.by8) {state->pc += 4; continue;}
			extractInt32(&instrs[state->pc], &ptj);
			state->pc += ptj;
			break;
		 
        case instrFuncCall:
			extractInt64(&instrs[state->pc], (int64_t*) &ptu);
			state->pc += 4;
			ctState_setupFuncFrame(state, ptu);
			break;

        case instrReturn:
			ctState_returnFuncFrame(state);
			break;

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

