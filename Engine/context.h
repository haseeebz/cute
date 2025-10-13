#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "atom.h"

#include <stdint.h>

#pragma once

typedef struct
{
	ProgramImage* program;
	ExecutionStack* exestack;
	int32_t pc;
} ExecutionContext;


ExecutionContext* ExecutionContext_init(ProgramImage* program);
void ExecutionContext_end(ExecutionContext* ctx);

