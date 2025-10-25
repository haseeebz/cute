#include <stdint.h>

// Definition of Cute cell, the singular unit for all storage within the engine

#pragma once 


typedef enum {typeInt32, typeFloat32} CellType;

typedef struct
{
    CellType type;

    union 
    {
        int32_t i;
        float f;
    } val;
    
} CuteCell;