#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


#pragma once
 
#ifdef __cplusplus
extern "C" {
#endif

// probably important
typedef int8_t ctInstrSize;


// main instruction set
typedef enum
{

    instrHalt       = 0x00,
	
	instrLoadCoI    = 0x10,
	
	instrAddI       = 0x20,
	instrSubI       = 0x21,
	instrMulI       = 0x22,
	instrDivI       = 0x23,

	instrOutI       = 0x30,

} ctInstr;


// program image defs

typedef struct
{
	u_int32_t magic;
	u_int32_t instr_count;
} ctProgramHeader;


typedef struct
{
	ctProgramHeader header;
	ctInstrSize* instrs;
} ctProgramImage;


// to make error handling easier

typedef enum
{

	ctImageError_Success = 0x00,
	ctImageError_FileNotFound = 0x01,

} ctImageError;

void ctProgramImage_free(ctProgramImage* img);
ctImageError ctProgramImage_read(ctProgramImage* img, char* filepath);
ctImageError ctProgramImage_write(ctProgramImage* img, char* filepath);


#ifdef __cplusplus
}
#endif