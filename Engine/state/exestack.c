
#include <stdio.h>
#include <stdlib.h>

#include "exestack.h"
#include "CuteAtom.h"


void CtExeStack_init(CtExeStack *stack)
{
	stack->cap = EXESTACK_SIZE;
	stack->count = 0;
}


void CtExeStack_push(CtExeStack *stack, CtAtom atom) 
{
    if (stack->count >= stack->cap)
	{
		fprintf(stderr, "Stack overflow. Count:%d, Cap:%d\n", stack->count, stack->cap);
        exit(EXIT_FAILURE);
	}
    stack->atoms[stack->count++] = atom;
}


CtAtom CtExeStack_pop(CtExeStack *stack) 
{
    if (stack->count == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->atoms[--stack->count];
}


CtAtom *CtExeStack_peek(CtExeStack *stack) 
{
    if (stack->count == 0) return NULL;
    return &stack->atoms[stack->count - 1];
}

