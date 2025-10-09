#include <stdint.h>

#pragma once 


typedef union
{
	int32_t i;
	float f;
} StackItem;

typedef struct
{
	StackItem* items;
	StackItem memory[10];
	int size;
	int capacity;
} ExecutionStack;

ExecutionStack* ExecutionStack_new(int capacity);
void ExecutionStack_del(ExecutionStack* stack);

void ExecutionStack_resize(ExecutionStack* stack, int capacity);

void ExecutionStack_push(ExecutionStack* stack, StackItem item);
StackItem ExecutionStack_pop(ExecutionStack* stack);
StackItem ExecutionStack_peek(ExecutionStack* stack);
