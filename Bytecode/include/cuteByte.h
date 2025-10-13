#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#pragma once 

#define MAGIC 0x10211225

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



typedef struct
{
	int32_t magic;
	int32_t instr_count;
} ProgramHeader;


typedef struct 
{
	ProgramHeader header;

	//ConstantValue* constant_pool;
	//size_t const_count;
	//size_t _const_cap;

	Instruction* instrs;
	size_t instr_count;

	size_t _instr_cap;

} ProgramSource;



ProgramSource* ProgramSource_new();
void ProgramSource_del(ProgramSource* program);

void ProgramSource_addInstruction(ProgramSource* program, Instruction instr);

int ProgramSource_addInt(ProgramSource* program, int32_t integar);


int ProgramSource_loadFromFile(ProgramSource* program, char* filepath);
int ProgramSource_writeToFile(ProgramSource* program, char* filepath);

void ProgramSource_print(ProgramSource* program);

#ifdef  __cplusplus 
}
#endif