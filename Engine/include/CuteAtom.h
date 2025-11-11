#include <stdint.h>
#include <stdbool.h>

// Definition of Cute Atom, the singular unit for all storage within the engine

#pragma once 

#ifdef __cplusplus
extern "C" {
#endif


// Primitives
typedef int32_t ctInt32;
typedef float   ctFloat32;
typedef int8_t  ctInt8;

// Special Primitives
// These will be distributed over 2 atoms
typedef int64_t ctInt64;
typedef double  ctFloat64;




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

struct _ctAtom
{
    AtomType type;

    union 
    {
        ctInt32   i;
        ctFloat32 f;
        ctInt8    by;
    };
    
};


typedef struct _ctAtom ctAtom;

#ifdef __cplusplus
}
#endif