#include <stdint.h>

#include "CuteAtom.h"

#pragma once 



typedef struct
{
    ctAtom *atoms;
    int count;
    int cap;
} ExeStack;


void ExeStack_init(ExeStack *stack, int initial_capacity);
void ExeStack_resize(ExeStack *stack, int new_cap);
void ExeStack_end(ExeStack *stack);

void ExeStack_push(ExeStack *stack, ctAtom atom);
ctAtom ExeStack_pop(ExeStack *stack);
ctAtom *ExeStack_peek(ExeStack *stack);

