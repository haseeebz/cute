#include <stdint.h>

#include "CuteAtom.h"

#pragma once 

#define EXESTACK_SIZE 1024


typedef struct
{
    ctAtom atoms[EXESTACK_SIZE];
    int count;
    int cap;
} ctExeStack;


void ctExeStack_init(ctExeStack *stack);

void ctExeStack_push(ctExeStack *stack, ctAtom atom);
ctAtom ctExeStack_pop(ctExeStack *stack);
ctAtom *ctExeStack_peek(ctExeStack *stack);