#include <stdint.h>
#pragma once 

typedef uint8_t OpCodeByte;

typedef enum
{
	opEXIT   = 0x01,  // Causes the engine to shutdown

	opLOADi  = 0x10,
	opSTORi  = 0x11,
	
	opADDi   = 0xA1, 
	opSUBi   = 0xA2, 
	opMULi   = 0xA3, 
	opDIVi   = 0xA4, 

	opOUT    = 0x88
} OpCode;


