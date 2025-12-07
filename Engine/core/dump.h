#include <stdio.h>

#include "CuteByte.h"
#include "context.h"


#pragma once 


void dump_handler(ctContext* ctx, int level);


void dump_Function(ctContext* ctx);
void dump_FunctionStack(ctContext* ctx);
void dump_Context(ctContext* ctx);
void dump_Engine(ctContext* ctx);
