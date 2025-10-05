#include <stdint.h>
#pragma once 

typedef uint8_t OpCodeByte;

typedef enum
{
	opLOADi = 0x01, // Expects a register and an integar
	opADDi = 0x02,
	opSUBi = 0x03,
	opOUT = 0x04,
	opHALT = 0x05,
} OpCode;

