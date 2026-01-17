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


/*
Base cute lib file. Include this in every single c file that the compiler spits out.

Functions, struct and global variables are namespaced as:

namespace_subNamespace__##__funcName

namespace_subNamespace__##__funcName__overloadInfo

namespace_subNamespace__##__structName

namespace_subNamespace__##__structName__method


The first namespace can be one of the following:
cute_ >> Stuff defined in this library
lang_ >> Stuff defined by the stdlib of the compiler
prog_ >> Stuff defined by the written program

*/

#include "CuteCore.h"
#include "CuteTypes.h"
#include "CuteContainer.h"
#include "CuteArray.h"
#include "CuteDyArray.h"