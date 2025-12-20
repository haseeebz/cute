#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


#pragma once
 
#ifdef __cplusplus
extern "C" {
#endif

static const uint32_t ctMagicId = 0x20080807;



// main instr set
typedef enum
{
    instrExitEngine    = 0x00, 
    instrExit          = 0x01, 
    instrOut           = 0x02, 
    instrDump          = 0x03, 
    instrPopAtom       = 0x04, 
    instrDupAtom       = 0x05, 
    instrNull          = 0x06, 

    instrLoadCoI32     = 0x11, 
    instrLoadCoI64     = 0x12, 
    instrLoadCoF32     = 0x13, 
    instrLoadCoF64     = 0x14, 
    instrLoadConst     = 0x15, 

    instrLoadI         = 0x20, 
    instrLoadF         = 0x21, 

    instrGLoadI        = 0x22, 
    instrGLoadF        = 0x23, 

    instrStoreI        = 0x24, 
    instrStoreF        = 0x25, 

    instrGStoreI       = 0x26, 
    instrGStoreF       = 0x27, 

    instrCopyI         = 0x28, 
    instrCopyF         = 0x29, 

    instrAddI          = 0xA0, 
    instrAddF          = 0xA1, 

    instrSubI          = 0xA2, 
    instrSubF          = 0xA3, 

    instrMulI          = 0xA4, 
    instrMulF          = 0xA5, 

    instrDivI          = 0xA6, 
    instrDivF          = 0xA7, 
    instrDivU          = 0xA8, 

    instrModI          = 0xA9, 
    instrModU          = 0xAA, 

    instrLogicAnd      = 0xB0, 
    instrLogicOr       = 0xB1, 
    instrLogicNot      = 0xB2, 
    instrLogicXor      = 0xB3, 

    instrBitAnd        = 0xB4, 
    instrBitOr         = 0xB5, 
    instrBitNot        = 0xB6, 
    instrBitXor        = 0xB7, 

    instrBitLShift     = 0xB8, 
    instrBitRShift     = 0xB9, 
    instrBitRaShift    = 0xBA, 

    instrCmpI          = 0xBB, 
    instrCmpF          = 0xBC, 
    instrCmpU          = 0xBD, 

    instrCmp2BoolEq    = 0x30, 
    instrCmp2BoolNe    = 0x31, 
    instrCmp2BoolLt    = 0x32, 
    instrCmp2BoolLe    = 0x33, 
    instrCmp2BoolGt    = 0x34, 
    instrCmp2BoolGe    = 0x35, 

    instrItoF          = 0x36, 
    instrFtoI          = 0x37, 

    instrJmp           = 0xD0, 
    instrJmpTrue       = 0xD1, 
    instrJmpFalse      = 0xD2, 

    instrFuncCall      = 0xD3, 
    instrReturn        = 0xD4, 

    instrConNew        = 0xC0, 
    instrConDel        = 0xC1, 
    instrConStore      = 0xC2, 
    instrConGStore     = 0xC3, 
    instrConLoad       = 0xC4, 
    instrConGLoad      = 0xC5, 
    instrConCopy       = 0xC6, 
    instrConClone      = 0xC7, 
    instrConAccLoad    = 0xC8, 
    instrConAccStore   = 0xC9, 
    instrConInc        = 0xCA, 
    instrConDec        = 0xCB

} ctInstr;


/*

Program Image Defs

*/

// Constant Pool

typedef struct
{
	uint32_t len;
	uint32_t size;
	uint64_t* data;
} ctConstArray;


typedef struct
{
	uint32_t len;
	char* data;
} ctConstString;

typedef struct
{
	enum {constArray, constString} type;
	union
	{
		ctConstArray array;
		ctConstString str;
	};

} ctProgramConstant;


// Function Table

typedef struct
{
	uint32_t func_id;
	uint32_t locals_count;
	uint32_t args_count;
	uint64_t instr_address;
} ctFuncMetadata;


// Instruction 
typedef uint8_t ctInstrSize;


typedef struct
{
	uint32_t magic;
	
	uint32_t const_count;

	uint32_t func_count;

	uint32_t instr_count;
} ctProgramHeader;


typedef struct
{
	ctProgramHeader header;
	ctProgramConstant* const_pool;
	ctFuncMetadata* func_table;
	ctInstrSize* instrs;
} ctProgramImage;


// to make error handling easier

typedef enum
{
	ctImageError_Success = 0x00,
	ctImageError_FileNotFound = 0x01,
	ctImageError_ReadWriteFailure = 0x02,
	ctImageError_InvalidImage = 0x03,
} ctImageError;


ctImageError ctProgramImage_read(ctProgramImage *img, char *filepath);
ctImageError ctProgramImage_write(ctProgramImage *img, char *filepath);

void ctProgramImage_freeImage(ctProgramImage *img);

void ctProgramImage_packInt32(int32_t *i, ctInstrSize *instr4); 
void ctProgramImage_packInt64(int64_t *i, ctInstrSize *instr8); 
void ctProgramImage_packFloat32(float *i, ctInstrSize *instr4); 
void ctProgramImage_packFloat64(double *i, ctInstrSize *instr8); 


#ifdef __cplusplus
}
#endif