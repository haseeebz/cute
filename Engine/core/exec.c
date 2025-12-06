#include "CuteEngine.h"
#include "CuteByte.h"
#include "CuteAtom.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "context.h"
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


static void outHandler(int fmt, ctAtom* atom)
{
	switch (fmt)
	{
		case 0:  goto binary; break;
		case 1:  printf("0x%lX\n", atom->u64); break;
		case 2:  printf("%d\n", atom->i32); break;
		case 3:  printf("%ld\n", atom->i64); break;
		case 4:  printf("%u\n", atom->u32); break;
		case 5:  printf("%lu\n", atom->u64); break;
		case 6:  printf("%f\n", atom->f32); break;
		case 7:  printf("%lf\n", atom->f64); break;
		default: printf("Invalid Format for Out instruction.\n"); break;
	}

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



void ctEngine_exec(ctContext *ctx)
{
	ctAtom a1;
	ctAtom a2;

	ctInstrSize *instrs = ctx->img->instrs;

	ctU32 ptu;
	ctU32 ptv;

	ctI32 pts;

	ctInstr instr;

	while (true)
	{

		if (!ctx->is_running)
		{
			if (ctx->error_encountered)
			{
				printf("%s :: %s\n", ctx->error.name, ctx->error.msg);
				ctEngine_end(1);
			}
		}

		instr = instrs[ctx->pc++];
	

		switch (instr)
		{

        case instrExitEngine:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx_end(ctx);
			ctEngine_end(pts);
			return;

        case instrExit:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx_end(ctx);
			return;

        case instrOut:
			extractInt32(&instrs[ctx->pc], &pts);
			ctx->pc += 4;
			a1 = ctx_peekExeAtom(ctx);
			outHandler(pts, &a1);
			break;

        case instrDump:
			printf("Dump instruction not implemented yet.\n");
			break;

        case instrPopAtom:
			ctx_popExeAtom(ctx);
			break;

        case instrDupAtom:
			ctx_pushExeAtom(ctx, ctx_peekExeAtom(ctx));
			break;

        case instrNull:
			break;

        case instrModCall:
			printf("ModCall instruction not implemented yet.\n");
			break;

        case instrLoadCoI32:
			extractInt32(&instrs[ctx->pc], &a1.i32);
			ctx->pc += 4;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLoadCoI64:
			extractInt64(&instrs[ctx->pc], &a1.i64);
			ctx->pc += 8;
			ctx_pushExeAtom(ctx, a1);
			break;

        case instrLoadCoF32:
			extractFloat32(&instrs[ctx->pc], &a1.f32);
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

        case instrLoadI32:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_pushExeAtom(ctx, ctx_loadLocal(ctx, ptu));
			break;

        case instrLoadI64:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 8;
			ctx_pushExeAtom(ctx, ctx_loadLocal(ctx, ptu));
			break;

        case instrLoadF32:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 8;
			ctx_pushExeAtom(ctx, ctx_loadLocal(ctx, ptu));
			break;

        case instrLoadF64:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 8;
			ctx_pushExeAtom(ctx, ctx_loadLocal(ctx, ptu));
			break;

        case instrGLoadI32:
			printf("GLoad instruction not implemented yet.\n");
			break;

        case instrGLoadI64:
			printf("GLoad instruction not implemented yet.\n");
			break;

        case instrGLoadF32:
			printf("GLoad instruction not implemented yet.\n");
			break;

        case instrGLoadF64:
			printf("GLoad instruction not implemented yet.\n");
			break;

        case instrStoreI32:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_storeLocal(ctx, ptu, ctx_popExeAtom(ctx));
			break;

        case instrStoreI64:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 8;
			ctx_storeLocal(ctx, ptu, ctx_popExeAtom(ctx));
			break;

        case instrStoreF32:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 4;
			ctx_storeLocal(ctx, ptu, ctx_popExeAtom(ctx));
			break;

        case instrStoreF64:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			ctx->pc += 8;
			ctx_storeLocal(ctx, ptu, ctx_popExeAtom(ctx));
			break;

        case instrGStoreI32:
			printf("GStore instruction not implemented yet.\n");
			break;

        case instrGStoreI64:
			printf("GStore instruction not implemented yet.\n");
			break;

        case instrGStoreF32:
			printf("GStore instruction not implemented yet.\n");
			break;

        case instrGStoreF64:
			printf("GStore instruction not implemented yet.\n");
			break;

        case instrCopyI32:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptv);
			ctx->pc += 8;
			ctx_copyLocal(ctx, ptu, ptv);
			break;

        case instrCopyI64:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptv);
			ctx->pc += 8;
			ctx_copyLocal(ctx, ptu, ptv);
			break;

        case instrCopyF32:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptv);
			ctx->pc += 8;
			ctx_copyLocal(ctx, ptu, ptv);
			break;

        case instrCopyF64:
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptu);
			extractInt32(&instrs[ctx->pc], (int32_t*)&ptv);
			ctx->pc += 8;
			ctx_copyLocal(ctx, ptu, ptv);
			break;

        case instrAddI32:
			mCtBinaryOp(i32, a1, a2, +, ctx);
			break;

		case instrAddI64:
			mCtBinaryOp(i64, a1, a2, +, ctx);
			break;

		case instrAddF32:
			mCtBinaryOp(f32, a1, a2, +, ctx);
			break;

		case instrAddF64:
			mCtBinaryOp(f64, a1, a2, +, ctx);
			break;

		case instrSubI32:
			mCtBinaryOp(i32, a1, a2, -, ctx);
			break;

		case instrSubI64:
			mCtBinaryOp(i64, a1, a2, -, ctx);
			break;

		case instrSubF32:
			mCtBinaryOp(f32, a1, a2, -, ctx);
			break;

		case instrSubF64:
			mCtBinaryOp(f64, a1, a2, -, ctx);
			break;

		case instrMulI32:
			mCtBinaryOp(i32, a1, a2, *, ctx);
			break;

		case instrMulI64:
			mCtBinaryOp(i64, a1, a2, *, ctx);
			break;

		case instrMulF32:
			mCtBinaryOp(f32, a1, a2, *, ctx);
			break;

		case instrMulF64:
			mCtBinaryOp(f64, a1, a2, *, ctx);
			break;

		case instrDivI32:
			mCtBinaryOp(i32, a1, a2, /, ctx);
			break;

		case instrDivI64:
			mCtBinaryOp(i64, a1, a2, /, ctx);
			break;

		case instrDivF32:
			mCtBinaryOp(f32, a1, a2, /, ctx);
			break;

		case instrDivF64:
			mCtBinaryOp(f64, a1, a2, /, ctx);
			break;

		case instrDivU32:
			mCtBinaryOp(u32, a1, a2, /, ctx);
			break;

		case instrDivU64:
			mCtBinaryOp(u64, a1, a2, /, ctx);
			break;

		case instrModI32:
			mCtBinaryOp(i32, a1, a2, %, ctx);
			break;

		case instrModU32:
			mCtBinaryOp(u32, a1, a2, %, ctx);
			break;

		case instrModI64:
			mCtBinaryOp(i64, a1, a2, %, ctx);
			break;

		case instrModU64:
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

        case instrBitRShift32:
			mCtBinaryOp(u32, a1, a2, >>, ctx);
			break;

        case instrBitRaShift32:
			mCtBinaryOp(i32, a1, a2, >>, ctx);
			break;

        case instrCmpI32:
			mCtCmpOp(i32, a1, a2, ctx);
			break;

        case instrCmpI64:
			mCtCmpOp(i64, a1, a2, ctx);
			break;

        case instrCmpF32:
			mCtCmpOp(f32, a1, a2, ctx);
			break;

        case instrCmpF64:
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

       case instrF32I32:
			a1 = ctx_popExeAtom(ctx);
			a1.i32 = (ctI32)a1.f32;
			ctx_pushExeAtom(ctx, a1);
		break;

		case instrI32F32:
			a1 = ctx_popExeAtom(ctx);
			a1.f32 = (ctF32)a1.i32;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrI64F64:
			a1 = ctx_popExeAtom(ctx);
			a1.f64 = (ctF64)a1.i64;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrF64I64:
			a1 = ctx_popExeAtom(ctx);
			a1.i64 = (ctI64)a1.f64;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrF32F64:
			a1 = ctx_popExeAtom(ctx);
			a1.f64 = (ctF64)a1.f32;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrF64F32:
			a1 = ctx_popExeAtom(ctx);
			a1.f32 = (ctF32)a1.f64;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrI32I64:
			a1 = ctx_popExeAtom(ctx);
			a1.i64 = (ctI64)a1.i32;
			ctx_pushExeAtom(ctx, a1);
			break;

		case instrI64I32:
			a1 = ctx_popExeAtom(ctx);
			a1.i32 = (ctI32)a1.i64;
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
