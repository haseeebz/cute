#include <stdint.h>
#pragma once 

typedef uint8_t OpCodeByte;

typedef enum
{
	opEXIT   = 0x01,  // Causes the engine to shutdown

	opLOADi  = 0x10,  
	opSTORi  = 0x11,
	opLCONi  = 0x12,

	opJMPx   = 0x20,  // Jump by offset. 
	opJMPe   = 0x21,  // Jump by offset if the last item in the stack is 1.

	opEQi    = 0x30,  // Pushes 1 if both integars are equal
	opGRi    = 0x31,
	opLRi    = 0x32,
	opGEi    = 0x33,
	opLEi    = 0x34,    

	opADDi   = 0xA1, 
	opSUBi   = 0xA2, 
	opMULi   = 0xA3, 
	opDIVi   = 0xA4, 


	opOUT    = 0x88  // Temporary instruction
} OpCode;


