#include "cuteInstr.h"
#include "cuteProgImg.h"

#include "atom.h"

#include <stdint.h>

#pragma once

typedef struct
{
	ExecutionStack exestack;
	int32_t pc;
} ExecutionContext;


void ExecutionContext_init(ExecutionContext* ctx);
void ExecutionContext_end(ExecutionContext* ctx);

