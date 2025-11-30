#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>


// Definition of Cute Atom, the singular unit for all storage within the engine
// This file defines the internal representation of stuff inside the Cute Lang
// Containers also defined here.

// Global header - Can be included by everything



#pragma once 

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t  ctI32;
typedef uint32_t ctU32;
typedef int64_t  ctI64;
typedef uint64_t ctU64;
typedef float    ctF32;
typedef double   ctF64;
typedef size_t   ctRef;


#define mCtBytecast(src, dest) \
static_assert(sizeof(*dest) == sizeof(*src), "Invalid bytecast! Trying to copy bytes between operands of different sizes!"); \
memcpy(dest, src, sizeof(*src));


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
        ctI32     i32;
		ctU32	  u32;	
		ctI64     i64;
		ctU64     u64;
        ctF32     f32;
		ctF64     f64;
		ctRef     ref;
		int8_t    by8;
    };
    
};


typedef struct _ctAtom ctAtom;

#ifdef __cplusplus
}

#endif