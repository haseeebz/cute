#include "state.h"
#include "exestack.h"


void CtState_init(CtState* state, ctProgramImage* img)
{
	CtExeStack_init(&state->exestack);
	state->pc = 0;
	state->img = img; // do not free. Is owned by the engine
}

void CtState_end(CtState* state)
{
	state->pc = 0;
}

void CtState_funcCall(CtState* state, uint32_t func_id)
{
}