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
typedef int64_t CtInt64;
typedef double  CtFloat64;

typedef uint64_t CtRefr;



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
        CtInt32   i32;
		CtInt64	  i64;	
        CtFloat32 f32;
		CtFloat64 f64;
        CtRefr    ref;
    };
    
};


typedef struct _CtAtom CtAtom;

#ifdef __cplusplus
}

#endif