#include <stdint.h>

#include "cell.h"

#pragma once 



typedef struct
{
    CuteCell *obj;
    int count;
    int cap;
} ExeStack;


void ExeStack_init(ExeStack *stack, int initial_capacity);
void ExeStack_resize(ExeStack *stack, int new_cap);
void ExeStack_end(ExeStack *stack);

void ExeStack_push(ExeStack *stack, CuteCell value);
CuteCell ExeStack_pop(ExeStack *stack);
CuteCell *ExeStack_peek(ExeStack *stack);

