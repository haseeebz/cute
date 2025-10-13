#include <stdint.h>

#pragma once



#ifdef  __cplusplus 
extern "C" {
#endif


typedef uint8_t InstrByte;

typedef enum
{
	
	instrEXIT       = 0x00,

	instrLOADi      = 0x10, // Load an integar from a given stack slot
	instrSTORi		= 0x11,	// Store an integar to a given address
	instrLCONi      = 0x12, // Load an integar from the constant pool

	instrADDi       = 0xA1,
	instrSUBi       = 0xA2,
	instrMULi       = 0xA3,
	instrDIVi       = 0xA4,
	
	instrOUT        = 0x88, // Temporary Instruction

} Instruction;


#ifdef  __cplusplus 
}
#endif


