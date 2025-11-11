
#include <stdio.h>
#include <stdlib.h>

#include "exestack.h"
#include "CuteAtom.h"


void ctExeStack_init(ctExeStack *stack)
{
	stack->cap = EXESTACK_SIZE;
	stack->count = 0;
}


void ctExeStack_push(ctExeStack *stack, ctAtom atom) 
{
    if (stack->count >= stack->cap)
	{
		fprintf(stderr, "Stack overflow. Count:%d, Cap:%d\n", stack->count, stack->cap);
        exit(EXIT_FAILURE);
	}
    stack->atoms[stack->count++] = atom;
}


ctAtom ctExeStack_pop(ctExeStack *stack) 
{
    if (stack->count == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->atoms[--stack->count];
}


ctAtom *ctExeStack_peek(ctExeStack *stack) 
{
    if (stack->count == 0) return NULL;
    return &stack->atoms[stack->count - 1];
}

