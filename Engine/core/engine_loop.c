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

	int64_t i1;
	int64_t i2;
	int64_t i3;
	int64_t p;
	
	double f1;
	double f2;



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
			break;

        case instrLoadCoI8:
			break;

        case instrLoadCoI32:
			i1 = consts[instrs[state->pc++]].i32;
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i1});
			break;

        case instrLoadCoI64:
			i1 = consts[instrs[state->pc++]].i64;
			mCt64To32(i1, i1, i2);
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i1});
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i2});
			break;

        case instrLoadCoF32:
			f1 = consts[instrs[state->pc++]].f32;
			CtExeStack_push(&state->exestack, (CtAtom) {.f = f1});
			break;

        case instrLoadCoF64:
			f1 = consts[instrs[state->pc++]].f64;
			mCt64To32(f1, f1, f2);
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i1});
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i2});
			break;
		
        case instrLoadI32:
			p = instrs[state->pc++];
			i1 = locals[p].i;
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i1});
			break;

        case instrLoadI64:
			p = instrs[state->pc++];
			i1 = locals[p].i;
			i2 = locals[p+1].i;
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i1});
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i2});
			break;

        case instrLoadF32:
			p = instrs[state->pc++];
			f1 = locals[p].f;
			CtExeStack_push(&state->exestack, (CtAtom) {.f = f1});
			break;

        case instrLoadF64:
			p = instrs[state->pc++];
			f1 = locals[p].f;
			f2 = locals[p+1].f;
			CtExeStack_push(&state->exestack, (CtAtom) {.f = f1});
			CtExeStack_push(&state->exestack, (CtAtom) {.f = f2});
			break;

        case instrStoreI32:
			p = instrs[state->pc++];
			locals[p] = CtExeStack_pop(&state->exestack);
			break;

        case instrStoreI64:
			p = instrs[state->pc++];
			locals[p+1] = CtExeStack_pop(&state->exestack); // low is popped first
			locals[p] = CtExeStack_pop(&state->exestack);
			break;

        case instrStoreF32:
			p = instrs[state->pc++];
			locals[p] = CtExeStack_pop(&state->exestack);
			break;

        case instrStoreF64:
			p = instrs[state->pc++];
			locals[p+1] = CtExeStack_pop(&state->exestack); // low is popped first
			locals[p] = CtExeStack_pop(&state->exestack);
			break;

        case instrAddI32:
			mCtBinaryOp32(i, i1, i2, +, &state->exestack);
			break;

        case instrAddI64:
			mCtBinaryOp64(i, i1, i2, i3, +, &state->exestack);
			break;

        case instrAddF32:
			mCtBinaryOp32(f, f1, f2, +, &state->exestack);
			break;

        case instrAddF64:
			mCtBinaryOp64(f, i1, i2, i3, +, &state->exestack);
			break;

        case instrSubI32:
			mCtBinaryOp32(i, i1, i2, -, &state->exestack);
			break;

        case instrSubI64:
			mCtBinaryOp64(i, i1, i2, i3, -, &state->exestack);
			break;

        case instrSubF32:
			mCtBinaryOp32(f, f1, f2, -, &state->exestack);
			break;

        case instrSubF64:
			mCtBinaryOp64(f, i1, i2, i3, -, &state->exestack);
			break;

        case instrMulI32:
			mCtBinaryOp32(i, i1, i2, *, &state->exestack);
			break;

        case instrMulI64:
			mCtBinaryOp64(i, i1, i2, i3, *, &state->exestack);
			break;

        case instrMulF32:
			mCtBinaryOp32(f, f1, f2, *, &state->exestack);
			break;

        case instrMulF64:
			mCtBinaryOp64(f, i1, i2, i3, *, &state->exestack);
			break;

        case instrDivI32:
			mCtBinaryOp32(i, i1, i2, /, &state->exestack);
			break;

        case instrDivI64:
			mCtBinaryOp64(i, i1, i2, i3, /, &state->exestack);
			break;

        case instrDivF32:
			mCtBinaryOp32(f, f1, f2, /, &state->exestack);
			break;

        case instrDivF64:
			mCtBinaryOp64(f, i1, i2, i3, /, &state->exestack);
			break;

        case instrXor:
			break;

        case instrCmpI32:
			i2 = CtExeStack_pop(&state->exestack).i;
			i1 = CtExeStack_pop(&state->exestack).i;
			if (i1 < i2) {i1 = -1;}
			else if (i1 > i2) {i1 = 1;}
			else  {i1 = 0;}
			CtExeStack_push(&state->exestack, (CtAtom) {.i = i1});
			break;

        case instrCmpI64:
        case instrCmpF32:
        case instrCmpF64:
        case instrCmp2BoolEq:
        case instrCmp2BoolNe:
        case instrCmp2BoolLt:
        case instrCmp2BoolLe:
        case instrCmp2BoolGt:
        case instrCmp2BoolGe:
        case instrJmp:
			p = instrs[state->pc++];
			state->pc = p;
			break;
        case instrJmpTrue:
        case instrJmpFalse:
        case instrCall:
        case instrCallVirtual:
        case instrReturn:
        case instrNewCon:
        case instrAccessCon:
        case instrDelCon:
		case instrOutI32:
			i1 = CtExeStack_peek(&state->exestack)->i;
			printf("%d\n", (int32_t) i1);
			break;

		case instrOutF32:
			f1 = CtExeStack_peek(&state->exestack)->f;
			printf("%f\n", (float) f1);
			break;

		case instrOutI64:
			i2 = CtExeStack_peek(&state->exestack)->r;
			i1 = CtExeStack_peek(&state->exestack)->r;
			mCt32To64(i1, i2, i1);
			printf("%ld\n", i1);
			break;

		case instrOutF64:
			i2 = CtExeStack_peek(&state->exestack)->r;
			i1 = CtExeStack_peek(&state->exestack)->r;
			mCt32To64(i1, i2, f1);
			printf("%lf\n", f1);
			break;
    }
	
	}

}

