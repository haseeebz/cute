#include <stdint.h>
#include <stdio.h>

#pragma once

#define CUTE_C_ADD   +
#define CUTE_C_SUB   -
#define CUTE_C_MUL   *
#define CUTE_C_DIV   /
#define CUTE_C_MOD   %

#define CUTE_C_EQ    ==
#define CUTE_C_NE    !=
#define CUTE_C_LT    <
#define CUTE_C_LE    <=
#define CUTE_C_GT    >
#define CUTE_C_GE    >=

#define CUTE_C_SHL   <<
#define CUTE_C_SHR   >>
#define CUTE_C_BAND  &
#define CUTE_C_BOR   |
#define CUTE_C_BXOR  ^

#define CUTE_C_LAND  &&
#define CUTE_C_LOR   ||


typedef int32_t  cute_I32;
typedef int64_t  cute_I64;
typedef uint32_t cute_U32;
typedef uint64_t cute_U64;
typedef float    cute_F32;
typedef double   cute_F64;

typedef uint8_t  cute_Bool;
typedef char     cute_Char;


#include "CuteCore.h"
#include "CuteContainer.h"
#include "CuteArray.h"
#include "CuteDyArray.h"