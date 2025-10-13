#include "atom.h"

#include <stddef.h>
#include <stdlib.h>


ExecutionStack* ExecutionStack_new(int32_t capacity)
{
	ExecutionStack* stack = malloc(sizeof(ExecutionStack));
	stack->atoms = malloc(sizeof(Atom) * capacity);
	stack->cap = capacity;
	stack->count = 0;
	return stack;
}


void ExecutionStack_del(ExecutionStack* stack)
{
	free(stack->atoms);
	free(stack);
}


void ExecutionStack_resize(ExecutionStack* stack, int32_t capacity)
{
	if (stack->count >= capacity) {return;}

	Atom* atoms = malloc(sizeof(Atom) * capacity);

	for (int i = 0; i < stack->count; i++)
	{
		atoms[i] = stack->atoms[i];
	}

	free(stack->atoms);

	stack->atoms = atoms;
	stack->cap = capacity;
}


void ExecutionStack_pushAtom(ExecutionStack* stack, Atom atom)
{
	if (stack->count >= stack->cap)
	{
		ExecutionStack_resize(stack, stack->cap * 2);
	}

	stack->atoms[stack->count] = atom;
	stack->count++;
}

Atom ExecutionStack_popAtom(ExecutionStack* stack)
{
	return stack->atoms[--stack->count];
}

Atom ExecutionStack_peekAtom(ExecutionStack* stack)
{
	return stack->atoms[stack->count - 1];
}