#include <stddef.h>
#include <stdint.h>


#pragma once
 
#ifdef __cplusplus
extern "C" {
#endif

typedef int8_t CtInstrSize;

typedef enum
{

    instrHalt = 0x00,
	
	instrLoadCoI = 0x10,
	
	instrAddI = 0x20,
	instrSubI = 0x21,
	instrMulI = 0x22,
	instrDivI = 0x23,

	instrOutI = 0x30,

} CtInstr;


typedef struct
{
    size_t instr_count;
    CtInstrSize* instrs;
} ProgramContext;


void ProgramContext_init(ProgramContext* ctx, CtInstrSize* instrs, size_t count);
void ProgramContext_end(ProgramContext* ctx);
void ProgramContext_read(ProgramContext* ctx, char* filepath);
void ProgramContext_write(ProgramContext* ctx, char* filepath);


#ifdef __cplusplus
}
#endif