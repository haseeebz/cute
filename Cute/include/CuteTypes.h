
#pragma once

#include <stdint.h>
#include <sys/types.h>


typedef struct
{
    int64_t val;
} cute_Int;

typedef struct 
{
    double val;
} cute_Float;

typedef struct
{
    u_int8_t val;
} cute_Bool;

typedef struct 
{
    char val;
} cute_Char;


// cute_Int
inline cute_Int
cute_Int__create__0(int64_t i);

inline cute_Int
cute_Int__create__1(cute_Float f);

inline int64_t
cute_Int__val(cute_Int self);


// cute_Float
inline cute_Float
cute_Float__create__0(double d);

inline cute_Float
cute_Float__create__1(cute_Int i);

inline double
cute_Float__val(cute_Float self);


// cute_Bool
inline cute_Bool
cute_Bool__create__0(cute_Int i);

// cute_Char
inline cute_Char
cute_Char__create__0(cute_Int i);
