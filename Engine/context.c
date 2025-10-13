#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "atom.h"
#include "context.h"

#include <stdint.h>
#include <stdlib.h>


ExecutionContext* ExecutionContext_init(ProgramImage* program)
{
	ExecutionContext* ctx = malloc(sizeof(ExecutionContext));
	ctx->exestack = ExecutionStack_new(10);
	ctx->program = program;
	ctx->pc = 0;
	return ctx;
}

void ExecutionContext_end(ExecutionContext* ctx)
{
	ExecutionStack_del(ctx->exestack);
	free(ctx);
}
