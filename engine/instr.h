#include <stdint.h>
#pragma once 

typedef uint8_t OpCodeByte;

typedef enum
{
	opEXIT  = 0x01, // Causes Engine to stop running.

	opLOADi = 0x02, // Rx Numerical - Loads the value at Address into Rx
	opLOADf = 0x03,	

	opSTRi  = 0x04, // Rx Address - Stores the thing at Rx into Address
	opSTRf  = 0x05,	

	opREADi = 0x06, // Rx Address - Loads the next x bytes into Rx
	opREADf = 0x07,

	opADDi  = 0x11,	// Rx Ry Rz - Adds Ry and Rz and stores result in Rx
	opSUBi  = 0x12,
	opMULi  = 0x13,
	opDIVi  = 0x14,

	opADDf  = 0x15,
	opSUBf  = 0x16,
	opMULf  = 0x17,
	opDIVf  = 0x18,

	opOUT   = 0x88, // Rx -  For printing, temporary instruction
} OpCode;


