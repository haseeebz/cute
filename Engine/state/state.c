#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "CuteAtom.h"
#include "CuteByte.h"
#include "CuteConfig.h"

#include "error.h"
#include "exestack.h"
#include "frame.h"

#include "state.h"


void ctState_init(ctState *state, ctProgramImage *img)
{
	state->img = img;
	state->func_table = img->func_table;

	state->exestack.cap = CUTE_EXESTACK_LIMIT;
	state->exestack.count = 0;

	state->frame_stack.cap = CUTE_FUNCSTACK_LIMIT;
	state->frame_stack.count = 0;

	state->error_encountered = false;
	state->isRunning = true;
}


void ctState_end(ctState *state)
{
	if (state->error_encountered)
	{
		ctError_free(&state->error);
	}

	state->exestack.count = 0;
	state->frame_stack.count = 0;
}


void ctState_pushExeAtom(ctState *state, ctAtom atom)
{
	if (state->exestack.count >= state->exestack.cap)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Overflow. No space for more atoms."
		);
		ctState_raiseError(state);
		return;
	}


	state->exestack.atoms[state->exestack.count++] = atom;
}


ctAtom ctState_popExeAtom(ctState *state)
{
	if (state->exestack.count <= 0)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Underflow. No more atoms to pop."
		);
		ctState_raiseError(state);
		return (ctAtom) {.i64 = 0};
	}

	return state->exestack.atoms[--state->exestack.count];
}


ctAtom ctState_peekExeAtom(ctState *state)
{
	if (state->exestack.count <= 0)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Underflow. No atoms to peek."
		);
		ctState_raiseError(state);
		return (ctAtom) {.i64 = 0};
	}

	return state->exestack.atoms[state->exestack.count-1];
}


ctProgramConst ctState_loadConst(ctState *state, uint32_t const_id)
{
	if (const_id >= state->img->header.const_count)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Const ID out of range."
		);
		ctState_raiseError(state);
		return (ctProgramConst) {.i64 = 0};
	}

	return state->const_table[const_id];
}


void ctState_setupFuncFrame(ctState *state, uint32_t func_id)
{

	if (func_id >= state->img->header.func_count)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Function ID out of range. Can not call."
		);
		ctState_raiseError(state);
		return;
	}

	if (state->frame_stack.count >= state->frame_stack.cap)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Max recursion depth reached."
		);
		ctState_raiseError(state);
		return;
	}


	ctFuncMetadata *meta = &state->func_table[func_id];
	
	if (meta->locals_size > CUTE_FUNCLOCALS_LIMIT)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Allocating too many locals for function."
		);
		ctState_raiseError(state);
		return;
	}
	else if (meta->arg_count > CUTE_ARG_LIMIT || meta->arg_count > meta->locals_size)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Passing too many arguments to function. Argument count is greater than arg limit or local memory size."
		);
		ctState_raiseError(state);
		return;
	}
	

	ctFuncFrame frame;
	frame.locals_count = meta->locals_size;
	frame.locals = malloc(sizeof(ctAtom) * meta->locals_size);
	
	for (int i = 0; i < meta->arg_count; i++)
	{
		ctAtom atom = ctState_popExeAtom(state);
		frame.locals[meta->arg_count - i - 1] = atom;
	}

	frame.return_address = state->pc;
	state->pc = meta->instr_address;

	state->frame_stack.frames[state->frame_stack.count++] = frame;
}


void ctState_returnFuncFrame(ctState *state)
{
	ctFuncFrame top_frame = state->frame_stack.frames[--state->frame_stack.count];
	free(top_frame.locals);

	state->pc = top_frame.return_address;

	if (state->frame_stack.count <= 0)
	{
		state->isRunning = false;
	}

}


void ctState_setLocal(ctState *state, uint32_t pos, ctAtom atom)
{
	ctFuncFrame top_frame = state->frame_stack.frames[state->frame_stack.count-1];

	if (pos >= top_frame.locals_count)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Invalid local store operation."
		);
		ctState_raiseError(state);
		return;
	}

	top_frame.locals[pos] = atom;
}


ctAtom ctState_getLocal(ctState *state, uint32_t pos)
{
	ctFuncFrame top_frame = state->frame_stack.frames[state->frame_stack.count-1];

	if (pos >= top_frame.locals_count)
	{
		state->isRunning = false;
		state->error_encountered = true;
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Invalid local load operation."
		);
		return (ctAtom) {.i64 = 0};
	}

	return top_frame.locals[pos];
}


void ctState_copyLocal(ctState *state, uint32_t src, uint32_t dest);


void ctState_raiseError(ctState *state)
{
	state->error_encountered = true;
	state->isRunning = false;
}