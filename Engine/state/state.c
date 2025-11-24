#include "CuteAtom.h"

#include "CuteByte.h"
#include "error.h"
#include "config.h"
#include "exestack.h"
#include "frame.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "state.h"



void ctState_init(ctState* state, ctProgramImage* img)
{
	state->img = img;
	state->func_table = img->func_table;

	state->exestack.cap = EXESTACK_LIMIT;
	state->exestack.count = 0;

	state->frame_stack.cap = FUNC_CALL_LIMIT;
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
		state->isRunning = false;
		state->error_encountered = true;

		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Overflow."
		);
		
		return;
	}


	state->exestack.atoms[state->exestack.count++] = atom;
}


ctAtom ctState_popExeAtom(ctState* state)
{
	if (state->exestack.count <= 0)
	{
		state->isRunning = false;
		state->error_encountered = true;

		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Underflow."
		);
		
		return (ctAtom) {.ref = 0};
	}

	return state->exestack.atoms[--state->exestack.count];
}


ctAtom ctState_peekExeAtom(ctState* state)
{
	if (state->exestack.count <= 0)
	{
		state->isRunning = false;
		state->error_encountered = true;

		ctError_new(
			&state->error,
			"Internal Cute Error",
			"ExeStack Underflow."
		);
		
		return (ctAtom) {.ref = 0};
	}

	return state->exestack.atoms[state->exestack.count-1];
}


void ctState_setupFuncFrame(ctState* state, uint32_t func_id)
{
	if (func_id >= state->img->header.func_count)
	{
		state->isRunning = false;
		state->error_encountered = true;
		printf("%d %d\n", func_id, state->img->header.func_count);
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Function id out of range."
		);
		return;
	}

	
	if (state->frame_stack.count >= state->frame_stack.cap)
	{
		state->isRunning = false;
		state->error_encountered = true;
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Max Recursion depth reached."
		);
		return;
	}

	// setting up the frame
	ctFuncMetadata* meta = &state->func_table[func_id];

	ctFuncFrame frame;
	frame.locals_count = meta->locals_size;
	frame.locals = malloc(sizeof(ctAtom) * meta->locals_size);

	printf("Executing function: %u\n", func_id);
	for (uint32_t i = 0; i < meta->arg_count; i++)
	{
		frame.locals[meta->arg_count-i-1] = ctState_popExeAtom(state);
	}
	
	// pushing frame
	state->pc = meta->address;
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
		state->isRunning = false;
		state->error_encountered = true;
		ctError_new(
			&state->error,
			"Internal Cute Error",
			"Invalid local set operation."
		);
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
		return (ctAtom) {.by8 = 0};
	}

	return top_frame.locals[pos];
}


void ctState_moveLocal(ctState* state, uint32_t src, uint32_t dest);
void ctState_copyLocal(ctState* state, uint32_t src, uint32_t dest);
