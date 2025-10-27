
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "atom.h"


void ExeStack_init(ExeStack *stack, int initial_capacity) 
{
    stack->cap = initial_capacity > 0 ? initial_capacity : 8;
    stack->count = 0;
    stack->atoms = (CtAtom*) malloc(stack->cap * sizeof(CtAtom));

    if (!stack->atoms)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}


void ExeStack_resize(ExeStack *stack, int new_cap) 
{
    CtAtom *new_mem = realloc(stack->atoms, new_cap * sizeof(CtAtom));
    if (!new_mem) {
        fprintf(stderr, "Stack resize failed\n");
        exit(EXIT_FAILURE);
    }
    stack->atoms = new_mem;
    stack->cap = new_cap;
}


void ExeStack_push(ExeStack *stack, CtAtom atom) 
{
    if (stack->count >= stack->cap)
        ExeStack_resize(stack, stack->cap * 2);
    stack->atoms[stack->count++] = atom;
}


CtAtom ExeStack_pop(ExeStack *stack) 
{
    if (stack->count == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->atoms[--stack->count];
}


CtAtom *ExeStack_peek(ExeStack *stack) 
{
    if (stack->count == 0) return NULL;
    return &stack->atoms[stack->count - 1];
}


void ExeStack_end(ExeStack *stack) 
{
    free(stack->atoms);
    stack->atoms = NULL;
    stack->count = 0;
    stack->cap = 0;
}
