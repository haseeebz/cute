#include <stdint.h>

// Definition of Cute Atom, the singular unit for all storage within the engine

#pragma once 


typedef enum {typeInt32, typeFloat32} AtomType;

typedef struct
{
    AtomType type;

    union 
    {
        int32_t i;
        float f;
    } val;
    
} CtAtom;