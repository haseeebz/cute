
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "cell.h"


void ExeStack_init(ExeStack *stack, int initial_capacity) 
{
    stack->cap = initial_capacity > 0 ? initial_capacity : 8;
    stack->count = 0;
    stack->obj = (CuteCell*) malloc(stack->cap * sizeof(CuteCell));

    if (!stack->obj)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}


void ExeStack_resize(ExeStack *stack, int new_cap) 
{
    CuteCell *new_mem = realloc(stack->obj, new_cap * sizeof(CuteCell));
    if (!new_mem) {
        fprintf(stderr, "Stack resize failed\n");
        exit(EXIT_FAILURE);
    }
    stack->obj = new_mem;
    stack->cap = new_cap;
}


void ExeStack_push(ExeStack *stack, CuteCell value) 
{
    if (stack->count >= stack->cap)
        ExeStack_resize(stack, stack->cap * 2);
    stack->obj[stack->count++] = value;
}


CuteCell ExeStack_pop(ExeStack *stack) 
{
    if (stack->count == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->obj[--stack->count];
}


CuteCell *ExeStack_peek(ExeStack *stack) 
{
    if (stack->count == 0) return NULL;
    return &stack->obj[stack->count - 1];
}


void ExeStack_end(ExeStack *stack) 
{
    free(stack->obj);
    stack->obj = NULL;
    stack->count = 0;
    stack->cap = 0;
}
