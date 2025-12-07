#include <stdio.h>

#include "CuteByte.h"
#include "context.h"
#include "dump.h"


void dump_handler(ctContext* ctx, int level)
{
	if (level == 0)
	{
		dump_Function(ctx);
	}
	else if (level == 1)
	{
		dump_FunctionStack(ctx);
	}
}


void dump_Function(ctContext* ctx)
{
	ctFuncFrame *frame = &ctx->funcstack.frames[ctx->funcstack.count-1];
	ctFuncMetadata meta = ctx->func_table[frame->id];

	printf("-- Function Dump --\n");
	printf("(Func Id: %d)\nArgs passed: %d; Local count: %d;\n", meta.func_id, meta.args_count, meta.locals_count);
	printf("Located at address: %ld;\n\n", meta.instr_address);

	printf("Locals Dump:\n");

	for (uint32_t i = 0; i < meta.locals_count; i++)
	{
		printf("%u : %016lX\n", i, frame->locals[i].u64);
	}
	printf("-- Dump Ended --\n");
}


void dump_FunctionStack(ctContext* ctx)
{
	printf("-- Function Stack Dump --\n");
	for (uint32_t i = 0; i <= ctx->funcstack.count - 1; i++)
	{
		ctFuncFrame *frame = &ctx->funcstack.frames[i];
		ctFuncMetadata meta = ctx->func_table[frame->id];
		printf(
			"(Func Id: %d) Args passed: %d; Local count: %d; Located at address: %ld;\n", 
			meta.func_id, meta.args_count, meta.locals_count, meta.instr_address
		);

		if (i != ctx->funcstack.count)
		{
		}
	}
	printf("-- Dump Ended --\n");
}