
#include <stdio.h>
#include <stdlib.h>

#include "exe.h"


void ExeStack_init(ExeStack *stack, int initial_capacity) 
{
    stack->cap = initial_capacity > 0 ? initial_capacity : 8;
    stack->count = 0;
    stack->obj = (CuteObj*) malloc(stack->cap * sizeof(CuteObj));

    if (!stack->obj)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}


void ExeStack_resize(ExeStack *stack, int new_cap) 
{
    CuteObj *new_mem = realloc(stack->obj, new_cap * sizeof(CuteObj));
    if (!new_mem) {
        fprintf(stderr, "Stack resize failed\n");
        exit(EXIT_FAILURE);
    }
    stack->obj = new_mem;
    stack->cap = new_cap;
}


void ExeStack_push(ExeStack *stack, CuteObj value) 
{
    if (stack->count >= stack->cap)
        ExeStack_resize(stack, stack->cap * 2);
    stack->obj[stack->count++] = value;
}


CuteObj ExeStack_pop(ExeStack *stack) 
{
    if (stack->count == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->obj[--stack->count];
}


CuteObj *ExeStack_peek(ExeStack *stack) 
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
