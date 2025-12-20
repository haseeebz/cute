#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


// Definition of Cute Atom, the singular unit for all storage within the engine
// This file defines the internal representation of stuff inside the Cute Lang
// Containers also defined here.

// Global header - Can be included by everything



#pragma once 

#ifdef __cplusplus
extern "C" {
#endif


struct CtAtom;
typedef struct CtAtom CtAtom;


typedef struct 
{
	uint32_t type_id;

	CtAtom* fields;
	uint32_t field_count;
} CtContainer;


// Atom Def

typedef enum
{

	atomInt,
	atomFloat,
	atomBool,
	atomContainer

} AtomType;


struct CtAtom
{
	AtomType type;
    
    union 
    {
		int64_t           i64;
		uint64_t          u64;
		double            f64;
		int64_t           b;
		CtContainer*      con;
    };
	
};




#ifdef __cplusplus
}

#endif