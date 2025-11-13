#include <stdint.h>

#include "CuteAtom.h"

#pragma once 

#define EXESTACK_SIZE 256


typedef struct
{
    ctAtom atoms[EXESTACK_SIZE];
    int count;
    int cap;
} CtExeStack;


void CtExeStack_init(CtExeStack *stack);

void CtExeStack_push(CtExeStack *stack, ctAtom atom);
ctAtom CtExeStack_pop(CtExeStack *stack);
ctAtom *CtExeStack_peek(CtExeStack *stack);