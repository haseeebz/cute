#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "atom.h"
#include "context.h"

#include <stdint.h>
#include <stdlib.h>


void ExecutionContext_init(ExecutionContext* ctx)
{
	ctx->exestack = ExecutionStack_init(10);
	ctx->pc = 0;
}

void ExecutionContext_end(ExecutionContext* ctx)
{
	ExecutionStack_del(&ctx->exestack);
	ctx->pc = 0;
}
