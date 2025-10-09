#include "frame.h"
#include <stdlib.h>


ExecutionStack* ExecutionStack_new(int capacity)
{
	ExecutionStack* stack = malloc(sizeof(ExecutionStack));
	stack->items = malloc(sizeof(StackItem) * capacity);
	stack->capacity = capacity;
	stack->size = 0;
	return stack;
}


void ExecutionStack_del(ExecutionStack* stack)
{
	free(stack->items);
	free(stack);
}


void ExecutionStack_resize(ExecutionStack* stack, int capacity)
{
	if (stack->capacity >= capacity) {return;}

	StackItem* items = malloc(sizeof(StackItem) * capacity);

	for (int i = 0; i < stack->size; i++)
	{
		items[i] = stack->items[i];
	}

	free(stack->items);

	stack->items = items;
	stack->capacity = capacity;
}


void ExecutionStack_push(ExecutionStack* stack, StackItem item)
{
	if (stack->size >= stack->capacity)
	{
		ExecutionStack_resize(stack, stack->capacity * 2);
	}

	stack->items[stack->size] = item;
	stack->size++;
}

StackItem ExecutionStack_pop(ExecutionStack* stack)
{
	stack->size--;
	return stack->items[stack->size];
}

StackItem ExecutionStack_peek(ExecutionStack* stack)
{
	return stack->items[stack->size-1];
}
