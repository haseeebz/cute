#include <stdbool.h>
#include <stdlib.h>

#include "CuteAtom.h"
#include "CuteByte.h"

#include "error.h"
#include "config.h"
#include "exestack.h"
#include "frame.h"

#include "state.h"


void ctState_init(ctState* state, ctProgramImage* img)
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


void ctState_end(ctState* state)
{
	if (state->error_encountered)
	{
		ctError_free(&state->error);
	}

	state->exestack.count = 0;
	state->frame_stack.count = 0;
}


void ctState_pushExeAtom(ctState* state, ctAtom atom)
{
	if (state->exestack.count >= state->exestack.cap)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Overflow."
		);
		ctState_raiseError(state);
		return;
	}


	state->exestack.atoms[state->exestack.count++] = atom;
}


ctAtom ctState_popExeAtom(ctState* state)
{
	if (state->exestack.count <= 0)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Underflow."
		);
		ctState_raiseError(state);
		return (ctAtom) {.i64 = 0};
	}

	return state->exestack.atoms[--state->exestack.count];
}


ctAtom ctState_peekExeAtom(ctState* state)
{
	if (state->exestack.count <= 0)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Underflow."
		);
		ctState_raiseError(state);
		return (ctAtom) {.i64 = 0};
	}

	return state->exestack.atoms[state->exestack.count-1];
}


ctProgramConst ctState_loadConst(ctState* state, uint32_t const_id)
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


void ctState_setupFuncFrame(ctState* state, uint32_t func_id)
{
	if (func_id >= state->img->header.func_count)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Function ID out of range."
		);
		ctState_raiseError(state);
		return;
	}

	
	if (state->frame_stack.count >= state->frame_stack.cap)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Max Recursion depth reached."
		);
		ctState_raiseError(state);
		return;
	}


	// setting up the frame
	ctFuncMetadata* meta = &state->func_table[func_id];

	ctFuncFrame frame;

	frame.locals_count = meta->locals_size;
	if (frame.locals_count > CUTE_LOCALS_LIMIT)
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Allocating too many locals for function."
		);
		ctState_raiseError(state);
	}
	frame.locals = malloc(sizeof(ctAtom) * meta->locals_size);
	
	// pushing frame
	state->pc = meta->instr_address;
	state->frame_stack.frames[state->frame_stack.count++] = frame;
}


void ctState_returnFuncFrame(ctState* state)
{
	ctFuncFrame top_frame = state->frame_stack.frames[--state->frame_stack.count];
	free(top_frame.locals);

	if (state->frame_stack.count <= 0)
	{
		state->isRunning = false;
	}

}


void ctState_setLocal(ctState* state, uint32_t pos, ctAtom atom)
{
	ctFuncFrame top_frame = state->frame_stack.frames[state->frame_stack.count-1];

	if (!(pos < top_frame.locals_count))
	{
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Invalid local set operation."
		);
		ctState_raiseError(state);
		return;
	}

	top_frame.locals[pos] = atom;
}


ctAtom ctState_getLocal(ctState* state, uint32_t pos)
{
	ctFuncFrame top_frame = state->frame_stack.frames[state->frame_stack.count-1];

	if (!(pos < top_frame.locals_count))
	{
		state->isRunning = false;
		state->error_encountered = true;
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Invalid local set operation."
		);
		return (ctAtom) {.i64 = 0};
	}

	return top_frame.locals[pos];
}


void ctState_copyLocal(ctState* state, uint32_t src, uint32_t dest);


void ctState_raiseError(ctState* state)
{
	state->error_encountered = true;
	state->isRunning = false;
}