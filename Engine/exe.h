#include <stdint.h>

#pragma once 


typedef struct
{
    union
    {
        int32_t i;
        float f;
    } val;
} CuteObj;


typedef struct
{
    CuteObj *obj;
    int count;
    int cap;
} ExeStack;


void ExeStack_init(ExeStack *stack, int initial_capacity);
void ExeStack_resize(ExeStack *stack, int new_cap);
void ExeStack_end(ExeStack *stack);

void ExeStack_push(ExeStack *stack, CuteObj value);
CuteObj ExeStack_pop(ExeStack *stack);
CuteObj *ExeStack_peek(ExeStack *stack);

