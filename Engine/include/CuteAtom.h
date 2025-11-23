#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Definition of Cute Atom, the singular unit for all storage within the engine

#pragma once 

#ifdef __cplusplus
extern "C" {
#endif



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

    union 
    {
        int32_t   i32;
		int64_t	  i64;	
        float     f32;
		double    f64;
        size_t    ref;
		int8_t	  by8;
    };
    
};


typedef struct _ctAtom ctAtom;

#ifdef __cplusplus
}

#endif