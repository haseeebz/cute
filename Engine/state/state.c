#include "CuteAtom.h"

#include "error.h"
#include "config.h"
#include "exestack.h"
#include "frame.h"
#include <stdlib.h>

#include "state.h"



void ctState_init(ctState* state, ctProgramImage* img)
{
	state->img = img;

	state->exestack.cap = EXESTACK_LIMIT;
	state->exestack.count = 0;

	state->frame_stack.cap = FUNC_CALL_LIMIT;
	state->frame_stack.count = 0;

	state->error_encountered = false;
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

void ctState_setupFuncFrame(ctState* state, uint32_t func_id);
void ctState_returnFuncFrame(ctState* state);

void ctState_setLocal(ctState* state, uint32_t pos, ctAtom* atom);
ctAtom ctState_getLocal(ctState* state, uint32_t pos);
void ctState_moveLocal(ctState* state, uint32_t src, uint32_t dest);
void ctState_copyLocal(ctState* state, uint32_t src, uint32_t dest);
