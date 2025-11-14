#include <stdint.h>

#include "CuteAtom.h"

#pragma once 

#define EXESTACK_SIZE 256


typedef struct
{
    CtAtom atoms[EXESTACK_SIZE];
    int count;
    int cap;
} CtExeStack;


void CtExeStack_init(CtExeStack *stack);

void CtExeStack_push(CtExeStack *stack, CtAtom atom);
CtAtom CtExeStack_pop(CtExeStack *stack);
CtAtom *CtExeStack_peek(CtExeStack *stack);