#include <stdint.h>

#include "atom.h"

#pragma once 



typedef struct
{
    CtAtom *atoms;
    int count;
    int cap;
} ExeStack;


void ExeStack_init(ExeStack *stack, int initial_capacity);
void ExeStack_resize(ExeStack *stack, int new_cap);
void ExeStack_end(ExeStack *stack);

void ExeStack_push(ExeStack *stack, CtAtom atom);
CtAtom ExeStack_pop(ExeStack *stack);
CtAtom *ExeStack_peek(ExeStack *stack);

