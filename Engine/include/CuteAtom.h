#include <stdint.h>
#include <stdbool.h>

// Definition of Cute Atom, the singular unit for all storage within the engine

#pragma once 

#ifdef __cplusplus
extern "C" {
#endif


// Primitives
typedef int32_t CtInt32;
typedef float   CtFloat32;

// Special Primitives
// These will be distributed over 2 atoms
typedef int64_t CtInt64;
typedef double  CtFloat64;

typedef uint32_t ctRaw32;




// Atom Types

typedef enum
{

    typeInt32,
    typeInt64,
    typeFloat32,
    typeFloat64,
    typeInt8

} AtomType;



// Main Atom def

struct _CtAtom
{
    AtomType type;

    union 
    {
        CtInt32   i;
        CtFloat32 f;
        ctRaw32   r;
    };
    
};


typedef struct _CtAtom CtAtom;

void CtAtom_Int32to64(CtAtom* a1, CtAtom* a2, int64_t* i);

#ifdef __cplusplus
}
#endif