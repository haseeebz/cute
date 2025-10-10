#include "frame.h"
#include "atom.h"
#include <stddef.h>
#include <stdlib.h>


ExecutionFrame* ExecutionFrame_new(size_t stack_cap, size_t memory_size)
{
	ExecutionFrame* frame = malloc(sizeof(ExecutionFrame));
	frame->stack = malloc(sizeof(Atom) * stack_cap);
	frame->stack_cap = stack_cap;
	frame->stack_size = 0;

	frame->memory = malloc(sizeof(Atom) * memory_size);
	frame->memory_size = memory_size;
	return frame;
}


void ExecutionFrame_del(ExecutionFrame* frame)
{
	free(frame->stack);
	free(frame->memory);
	free(frame);
}


void ExecutionFrame_resize(ExecutionFrame* frame, int capacity)
{
	if (frame->stack_cap >= capacity) {return;}

	Atom* new_stack = malloc(sizeof(Atom) * capacity);

	for (int i = 0; i < frame->stack_size; i++)
	{
		new_stack[i] = frame->stack[i];
	}

	free(frame->stack);

	frame->stack = new_stack;
	frame->stack_cap = capacity;
}


void ExecutionFrame_push(ExecutionFrame* frame, Atom atom)
{
	if (frame->stack_size >= frame->stack_cap)
	{
		ExecutionFrame_resize(frame, frame->stack_cap * 2);
	}

	frame->stack[frame->stack_size] = atom;
	frame->stack_size++;
}

Atom ExecutionFrame_pop(ExecutionFrame* frame)
{
	frame->stack_size--;
	return frame->stack[frame->stack_size];
}

Atom ExecutionFrame_peek(ExecutionFrame* frame)
{
	return frame->stack[frame->stack_size-1];
}


void ExecutionFrame_readAtom(ExecutionFrame* frame, size_t index, Atom* atoms, size_t size)
{
	if (index + size >= frame->memory_size)
	{
		return;
	}

	for (int i = index; i < index + size; i++)
	{
		atoms[i] = frame->memory[i];
	}
	
}

void ExecutionFrame_writeAtom(ExecutionFrame* frame, size_t index, Atom* atoms, size_t size)
{
	if (index + size >= frame->memory_size)
	{
		return;
	}

	for (int i = index; i < index + size; i++)
	{
		frame->memory[i] = atoms[i];
	}
}