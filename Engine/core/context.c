#include "CuteByte.h"
#include "CuteAtom.h"
#include "CuteConfig.h"

#include "error.h"
#include <stdlib.h>
#include "context.h"


void ctx_init(ctContext *ctx, ctProgramImage *img)
{
	ctx->pc = 0;
	ctx->is_running = true;
	ctx->error_encountered = false;

	ctx->exestack.count = 0;
	ctx->exestack.cap = CUTE_EXESTACK_LIMIT;

	ctx->funcstack.count = 0;
	ctx->funcstack.cap = CUTE_FUNCSTACK_LIMIT;

	ctx->img = img;
	ctx->func_table = img->func_table;
}


void ctx_end(ctContext *ctx)
{
	if (ctx->error_encountered)
	{
		error_free(&ctx->error);
	}

	ctx->exestack.count = 0;
	ctx->funcstack.count = 0;
}


void ctx_pushExeAtom(ctContext *ctx, CtAtom atom)
{
	if (ctx->exestack.count >= ctx->exestack.cap)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"ExeStack Overflow. No space for more atoms."
		);
		ctx_raiseError(ctx);
		return;
	}


	ctx->exestack.atoms[ctx->exestack.count++] = atom;
}


CtAtom ctx_popExeAtom(ctContext *ctx)
{
	if (ctx->exestack.count <= 0)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"ExeStack Underflow. No more atoms to pop."
		);
		ctx_raiseError(ctx);
		return (CtAtom) {.i64 = 0};
	}

	return ctx->exestack.atoms[--ctx->exestack.count];
}


CtAtom ctx_peekExeAtom(ctContext *ctx)
{
	if (ctx->exestack.count <= 0)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"ExeStack Underflow. No atoms to peek."
		);
		ctx_raiseError(ctx);
		return (CtAtom) {.i64 = 0};
	}

	return ctx->exestack.atoms[ctx->exestack.count-1];
}


void ctx_funcCall(ctContext *ctx, uint32_t func_id)
{

	if (func_id >= ctx->img->header.func_count)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Function ID out of range. Can not call."
		);
		ctx_raiseError(ctx);
		return;
	}

	if (ctx->funcstack.count >= ctx->funcstack.cap)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Max recursion depth reached."
		);
		ctx_raiseError(ctx);
		return;
	}


	ctFuncMetadata *meta = &ctx->func_table[func_id];
	
	if (meta->locals_count > CUTE_FUNCLOCALS_LIMIT)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Allocating too many locals for function."
		);
		ctx_raiseError(ctx);
		return;
	}
	else if (meta->args_count > CUTE_ARG_LIMIT || meta->args_count > meta->locals_count)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Passing too many arguments to function. Argument count is greater than arg limit or local memory size."
		);
		ctx_raiseError(ctx);
		return;
	}
	

	ctFuncFrame frame;
	frame.locals_count = meta->locals_count;
	frame.locals = malloc(sizeof(CtAtom) * meta->locals_count);
	
	for (uint32_t i = 0; i < meta->args_count; i++)
	{
		CtAtom atom = ctx_popExeAtom(ctx);
		frame.locals[meta->args_count - i - 1] = atom;
	}

	frame.id = meta->func_id;
	frame.return_address = ctx->pc;
	ctx->pc = meta->instr_address;

	ctx->funcstack.frames[ctx->funcstack.count++] = frame;
}


void ctx_funcReturn(ctContext *ctx)
{
	ctFuncFrame top_frame = ctx->funcstack.frames[--ctx->funcstack.count];
	free(top_frame.locals);

	ctx->pc = top_frame.return_address;

	if (ctx->funcstack.count <= 0)
	{
		ctx->is_running = false;
	}

}


void ctx_storeLocal(ctContext *ctx, uint32_t pos, CtAtom atom)
{
	ctFuncFrame top_frame = ctx->funcstack.frames[ctx->funcstack.count-1];

	if (pos >= top_frame.locals_count)
	{
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Invalid local store operation."
		);
		ctx_raiseError(ctx);
		return;
	}

	top_frame.locals[pos] = atom;
}


CtAtom ctx_loadLocal(ctContext *ctx, uint32_t pos)
{
	ctFuncFrame top_frame = ctx->funcstack.frames[ctx->funcstack.count-1];

	if (pos >= top_frame.locals_count)
	{
		ctx->is_running = false;
		ctx->error_encountered = true;
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Invalid local load operation."
		);
		return (CtAtom) {.i64 = 0};
	}

	return top_frame.locals[pos];
}


void ctx_copyLocal(ctContext *ctx, uint32_t src, uint32_t dest)
{
	ctFuncFrame top_frame = ctx->funcstack.frames[ctx->funcstack.count-1];

	if (src >= top_frame.locals_count || dest >= top_frame.locals_count)
	{
		ctx->is_running = false;
		ctx->error_encountered = true;
		error_new(
			&ctx->error,
			"Internal Cute Error",
			"Invalid local copy operation."
		);
		return;
	}

	top_frame.locals[dest] = top_frame.locals[src];
}


void ctx_raiseError(ctContext *ctx)
{
	ctx->error_encountered = true;
	ctx->is_running = false;
}