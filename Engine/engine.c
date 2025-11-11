#include "CuteAtom.h"
#include "CuteByte.h"
#include "CuteEngine.h"
#include "context/context.h"
#include "context/exestack.h"
#include <stdio.h>
#include <stdlib.h>


CuteEngine ctEngine;

void CuteEngine_init()
{
	return;
}


void CuteEngine_end()
{
	exit(EXIT_FAILURE);
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


CtContext* CuteEngine_newContext()
{
	CtContext* ctx = malloc(sizeof(CtContext));
	ctx->img = &ctEngine.img;
	ctx->pc = 0;

	return ctx;
}

void CuteEngine_endContext(CtContext** ctx)
{
	free(ctx);
	ctx = NULL;
}


void CuteEngine_runMain()
{
	CtContext* ctx = CuteEngine_newContext();
	
	CuteEngine_execLoop(ctx);

	CuteEngine_endContext(&ctx);
}


void CuteEngine_execLoop(CtContext* ctx)
{
	ctInstr instr;

	ctInstrSize* instrs = ctx->img->instrs;

	int64_t i1;
	int64_t i2;

	double f1;
	double f2;

	ctAtom a1;
	ctAtom a2;

	while (1)
	{

	instr = instrs[ctx->pc++];

	switch (instr) 
	{
        case instrHalt:
			return;

        case instrDupAtom:
			break;

        case instrPopAtom:
			break;

        case instrLoadCoI8:
			break;

        case instrLoadCoI32:
			i1 = instrs[ctx->pc++];
			a1.i = i1;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrLoadCoI64:
			break;

        case instrLoadCoF32:
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
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.i = a1.i + a2.i;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrAddI64:
			break;

        case instrAddF32:
			break;

        case instrAddF64:
			break;

        case instrSubI32:
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.i = a1.i - a2.i;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrSubI64:
			break;

        case instrSubF32:
			break;

        case instrSubF64:
			break;

        case instrMulI32:
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.i = a1.i * a2.i;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrMulI64:
			break;

        case instrMulF32:
			break;

        case instrMulF64:
			break;

        case instrDivI32:
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.i = a1.i / a2.i;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrDivI64:
			break;

        case instrDivF32:
			break;

        case instrDivF64:
			break;

        case instrAnd:
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.by = a1.by && a2.by;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrOr:
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.by = a1.by || a2.by;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrNot:
			a1 = ctExeStack_pop(&ctx->exestack);
			a1.i = !a1.i;
			ctExeStack_push(&ctx->exestack, a1);
			break;

        case instrXor:
			break;

        case instrCmpI32:
			a2 = ctExeStack_pop(&ctx->exestack);
			a1 = ctExeStack_pop(&ctx->exestack);
			if (a1.i < a2.i) {a1.i = -1;}
			else if (a1.i > a2.i) {a1.i = 1;}
			else  {a1.i = 0;}
			ctExeStack_push(&ctx->exestack, a1);
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
        case instrJmpTrue:
        case instrJmpFalse:
        case instrCall:
        case instrCallVirtual:
        case instrReturn:
        case instrNewCon:
        case instrAccessCon:
        case instrDelCon:
		case instrOut:
			a1 = *ctExeStack_peek(&ctx->exestack);
			printf("%d\n", a1.i);
			break;
    }

	
    }
}


