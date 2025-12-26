#include "CuteEngine.h"
#include "CuteByte.h"
#include "CuteAtom.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "context.h"
#include "dump.h"
#include "op.h"


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


static void outHandler(int fmt, CtAtom *atom)
{
	switch (fmt)
	{
		case 0:  goto binary; break;
		case 1:  printf("0x%016lX\n", atom->u64); break;
		case 2:  printf("%ld\n", atom->i64); break;
		case 3:  printf("%lu\n", atom->u64); break;
		case 4:  printf("%lf\n", atom->f64); break;
		default: printf("Invalid Format for Out instruction: %d\n", fmt); break;
	}
	return;

	uint64_t number;

	binary:
	
	number = atom->u64;
	for (int i = 63; i >= 0; i--)
	{
		if ( ((i+1) % 8 == 0) && (i != 63) ) {printf(" ");}
		int digit = ((number >> i) & 1);
		printf("%d", digit);
	}
	printf("\n");
}




void CuteEngine_exec(ctContext *ctx)
{
	CtAtom a1;
	CtAtom a2;

	ctInstrSize *instrs = ctx->img->instrs;

	uint32_t ptu;
	uint32_t ptv;

	int32_t  pts;
	float    ptf;

	ctInstr instr;

	while (true)
	{

		if (!ctx->is_running)
		{
			if (ctx->error_encountered)
			{
				printf("%s :: %s\n", ctx->error.name, ctx->error.msg);
				CuteEngine_end(1);
			}
		}

		instr = instrs[ctx->pc++];

		switch (instr)
		{

        case instrExitEngine:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx_end(ctx);
			CuteEngine_end(pts);
			return;

        case instrExit:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx_end(ctx);
			return;

        case instrOut:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx->pc += 4;
			a1 = ctx_popExeAtom(ctx);
			outHandler(pts, &a1);
			break;

        case instrDump:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx->pc += 4;
			dump_handler(ctx, pts);
			break;

        case instrPopAtom:
			ctx_popExeAtom(ctx);
			break;

        case instrDupAtom:
			ctx_pushExeAtom(ctx, ctx_peekExeAtom(ctx));
			break;

        case instrNull:
			break;

        case instrLoadCoI32:
			extractInt32(&instrs[ctx->pc], &pts);
			a1.i64 = pts;
			ctx->pc += 4;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLoadCoI64:
			extractInt64(&instrs[ctx->pc], &a1.i64);
			ctx->pc += 8;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLoadCoF32:
			extractFloat32(&instrs[ctx->pc], &ptf);
			a1.f64 = ptf;
			ctx->pc += 4;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLoadCoF64:
			extractFloat64(&instrs[ctx->pc], &a1.f64);
			ctx->pc += 8;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLoadConst:
			printf("LoadConst instruction not implemented yet.\n");
			break;

        case instrLoadI:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_pushExeAtom(ctx, ctx_loadLocal(ctx, ptu));
			break;

        case instrLoadF:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_pushExeAtom(ctx, ctx_loadLocal(ctx, ptu));
			break;

        case instrGLoadI:
			printf("GLoad instruction not implemented yet.\n");
			break;

        case instrGLoadF:
			printf("GLoad instruction not implemented yet.\n");
			break;

        case instrStoreI:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_storeLocal(ctx, ptu, ctx_popExeAtom(ctx));
			break;

        case instrStoreF:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_storeLocal(ctx, ptu, ctx_popExeAtom(ctx));
			break;

        case instrGStoreI:
			printf("GStore instruction not implemented yet.\n");
			break;

        case instrGStoreF:
			printf("GStore instruction not implemented yet.\n");
			break;

        case instrCopyI:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptv);
			ctx->pc += 8;
			ctx_copyLocal(ctx, ptu, ptv);
			break;

        case instrCopyF:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptv);
			ctx->pc += 8;
			ctx_copyLocal(ctx, ptu, ptv);
			break;

		case instrAddI:
			mCtBinaryOp(i64, a1, a2, +, ctx);
			break;

		case instrAddF:
			mCtBinaryOp(f64, a1, a2, +, ctx);
			break;

		case instrSubI:
			mCtBinaryOp(i64, a1, a2, -, ctx);
			break;
			
		case instrSubF:
			mCtBinaryOp(f64, a1, a2, -, ctx);
			break;

		case instrMulI:
			mCtBinaryOp(i64, a1, a2, *, ctx);
			break;

		case instrMulF:
			mCtBinaryOp(f64, a1, a2, *, ctx);
			break;

		case instrDivI:
			mCtBinaryOp(i64, a1, a2, /, ctx);
			break;

		case instrDivF:
			mCtBinaryOp(f64, a1, a2, /, ctx);
			break;

		case instrDivU:
			mCtBinaryOp(u64, a1, a2, /, ctx);
			break;

		case instrModI:
			mCtBinaryOp(i64, a1, a2, %, ctx);
			break;

		case instrModU:
			mCtBinaryOp(u64, a1, a2, %, ctx);
			break;

		case instrLogicAnd:
			mCtBinaryOp(i64, a1, a2, &&, ctx);
			break;

        case instrLogicOr:
			mCtBinaryOp(i64, a1, a2, ||, ctx);
			break;

        case instrLogicNot:
			a1.i64 = !ctx_popExeAtom(ctx).i64;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLogicXor:
			mCtBinaryOp(i64, a1, a2, !=, ctx);
			break;

        case instrBitAnd:
			mCtBinaryOp(u64, a1, a2, &, ctx);
			break;

        case instrBitOr:
			mCtBinaryOp(u64, a1, a2, |, ctx);
			break;

        case instrBitNot:
			a1.u64 = ~ctx_popExeAtom(ctx).u64;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrBitXor:
			mCtBinaryOp(u64, a1, a2, ^, ctx);
			break;

        case instrBitLShift:
			mCtBinaryOp(u64, a1, a2, <<, ctx);
			break;

        case instrBitRShift:
			mCtBinaryOp(u64, a1, a2, >>, ctx);
			break;

        case instrBitRaShift:
			mCtBinaryOp(i64, a1, a2, >>, ctx);
			break;

        case instrCmpI:
			mCtCmpOp(i64, a1, a2, ctx);
			break;

		case instrCmpU:
			mCtCmpOp(u64, a1, a2, ctx);
			break;

        case instrCmpF:
			mCtCmpOp(f64, a1, a2, ctx);
			break;
        
        case instrCmp2BoolEq:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64 == 0) {a1.i64 = 1;} else {a1.i64 = 0;}
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrCmp2BoolNe:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64 != 0) {a1.i64 = 1;} else {a1.i64 = 0;}
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrCmp2BoolLt:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64 == -1) {a1.i64 = 1;} else {a1.i64 = 0;}
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrCmp2BoolLe:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64 <= 0) {a1.i64 = 1;} else {a1.i64 = 0;}
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrCmp2BoolGt:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64 == 1) {a1.i64 = 1;} else {a1.i64 = 0;}
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrCmp2BoolGe:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64 >= 0) {a1.i64 = 1;} else {a1.i64 = 0;}
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrItoF:
			a1 = ctx_popExeAtom(ctx);
			a1.f64 = (double) a1.i64;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrFtoI:
			a1 = ctx_popExeAtom(ctx);
			a1.i64 = (int64_t) a1.f64;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrJmp:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx->pc += pts;
			break;

        case instrJmpTrue:
			a1 = ctx_popExeAtom(ctx);
			if (!a1.i64) {ctx->pc += 4; continue;}
			extractInt32(&instrs[ctx->pc], &pts);
			ctx->pc += pts;
			break;
		 
        case instrJmpFalse:
			a1 = ctx_popExeAtom(ctx);
			if (a1.i64) {ctx->pc += 4; continue;}
			extractInt32(&instrs[ctx->pc], &pts);
			ctx->pc += pts;
			break;

        case instrFuncCall:
			extractInt32(&instrs[ctx->pc], (int32_t*) &ptu);
			ctx->pc += 4;
			ctx_funcCall(ctx, ptu);
			break;

        case instrReturn:
			ctx_funcReturn(ctx);
			break;

        case instrConNew:
        case instrConDel:
        case instrConStore:
        case instrConGStore:
        case instrConLoad:
        case instrConGLoad:
        case instrConCopy:
        case instrConClone:
        case instrConAccLoad:
        case instrConAccStore:
        case instrConInc:
        case instrConDec:
			printf("Con instructions not implemented yet.\n");
			break;
		}


	}
}
