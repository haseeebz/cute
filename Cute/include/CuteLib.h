#include <stdlib.h>
#include <stdint.h>

#pragma once

typedef int32_t  cute_I32;
typedef int64_t  cute_I64;
typedef uint32_t cute_U32;
typedef uint64_t cute_U64;
typedef float    cute_F32;
typedef double   cute_F64;

typedef uint8_t  cute_Bool;
typedef char     cute_Char;


struct cute_Core
{
	void (*main)();
};

void cute_Core_run(void (*main)());

void cute_Core_init();
void cute_Core_end();

