
#pragma once

#include <stdint.h>


#define CUTE_INT_TYPE   "cute_Int"
#define CUTE_UINT_TYPE  "cute_UInt"
#define CUTE_FLOAT_TYPE "cute_Float"
#define CUTE_BOOL_TYPE  "cute_Bool"
#define CUTE_BYTE_TYPE  "cute_Byte"

typedef struct
{
    int64_t val;
} cute_Int;


typedef struct
{
    uint64_t val;
} cute_UInt;


typedef struct 
{
    double val;
} cute_Float;


typedef struct
{
    uint8_t val;
} cute_Bool;


typedef struct 
{
    char val;
} cute_Char;


typedef struct 
{
    uint8_t val;
} cute_Byte;


// cute_Int

inline cute_Int
cute_Int__create__0(int64_t c);

inline cute_Int
cute_Int__create__1(cute_Int c);

inline cute_Int
cute_Int__create__2(cute_UInt c);

inline cute_Int
cute_Int__create__3(cute_Float c);

inline cute_Int
cute_Int__create__4(cute_Bool c);

inline cute_Int
cute_Int__create__5(cute_Byte c);

inline int64_t
cute_Int__val(cute_Int i);



// cute_UInt

inline cute_UInt
cute_UInt__create__0(uint64_t c);

inline cute_UInt
cute_UInt__create__1(cute_UInt c);

inline cute_UInt
cute_UInt__create__2(cute_Int c);

inline uint64_t
cute_UInt__val(cute_UInt i);


// cute_Float

inline cute_Float
cute_Float__create__0(double c);

inline cute_Float
cute_Float__create__1(cute_Float c);

inline cute_Float
cute_Float__create__2(cute_Int c);

inline double
cute_Float__val(cute_Float f);


// cute_Bool

inline cute_Bool
cute_Bool__create__0(uint8_t c);

inline cute_Bool
cute_Bool__create__1(cute_Bool c);

inline cute_Bool
cute_Bool__create__2(cute_Int c);

inline cute_Bool
cute_Bool__create__3(cute_UInt c);

inline cute_Bool
cute_Bool__create__4(cute_Byte c);

inline uint64_t
cute_Bool__val(cute_Bool b);


// cute_Byte

inline cute_Byte
cute_Byte__create__0(uint8_t c);

inline cute_Byte
cute_Byte__create__1(cute_Byte c);

