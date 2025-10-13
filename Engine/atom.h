#include <stdint.h>
#include <stdbool.h>

#pragma once 


typedef struct 
{
	enum {atomInt, atomFloat} type;

	union 
	{
		int32_t i;
		float f;
	} val;
} Atom;


typedef struct
{	
	Atom* atoms;
	int32_t count;
	int32_t cap;
} ExecutionStack;


ExecutionStack ExecutionStack_init(int32_t capacity);
void ExecutionStack_del(ExecutionStack* stack);
void ExecutionStack_resize(ExecutionStack* stack, int32_t capacity);


bool ExecutionStack_isEmpty(ExecutionStack* stack);
void ExecutionStack_pushAtom(ExecutionStack* stack, Atom atom);
Atom ExecutionStack_popAtom(ExecutionStack* stack);
Atom ExecutionStack_peekAtom(ExecutionStack* stack);


