#pragma once 

#include <stddef.h>
#include <stdint.h>
#include "atom.h"

typedef struct
{
	Atom* stack;
	size_t stack_cap;
	size_t stack_size;

	Atom* memory;
	size_t memory_size;
} ExecutionFrame;

ExecutionFrame* ExecutionFrame_new(size_t stack_cap, size_t memory_size);
void ExecutionFrame_del(ExecutionFrame* frame);

void ExecutionFrame_resize(ExecutionFrame* stack, int capacity);

void ExecutionFrame_push(ExecutionFrame* frame, Atom atom);
Atom ExecutionFrame_pop(ExecutionFrame* frame);
Atom ExecutionFrame_peek(ExecutionFrame* frame);
