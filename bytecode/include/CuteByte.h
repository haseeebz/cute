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
    instrModCall       = 0x07, 

    instrLoadCoI32     = 0x08, 
    instrLoadCoI64     = 0x09, 
    instrLoadCoF32     = 0x0A, 
    instrLoadCoF64     = 0x0B, 
    instrLoadConst     = 0x0C, 

    instrLoadI32       = 0x0D, 
    instrLoadI64       = 0x0E, 
    instrLoadF32       = 0x0F, 
    instrLoadF64       = 0x10, 

    instrGLoadI32      = 0x11, 
    instrGLoadI64      = 0x12, 
    instrGLoadF32      = 0x13, 
    instrGLoadF64      = 0x14, 

    instrStoreI32      = 0x15, 
    instrStoreI64      = 0x16, 
    instrStoreF32      = 0x17, 
    instrStoreF64      = 0x18, 

    instrGStoreI32     = 0x19, 
    instrGStoreI64     = 0x1A, 
    instrGStoreF32     = 0x1B, 
    instrGStoreF64     = 0x1C,

    instrCopyI32       = 0x1D, 
    instrCopyI64       = 0x1E, 
    instrCopyF32       = 0x1F, 
    instrCopyF64       = 0x20, 

    instrAddI32        = 0x21, 
    instrAddI64        = 0x22, 
    instrAddF32        = 0x23, 
    instrAddF64        = 0x24, 

    instrSubI32        = 0x25, 
    instrSubI64        = 0x26, 
    instrSubF32        = 0x27, 
    instrSubF64        = 0x28, 

    instrMulI32        = 0x29, 
    instrMulI64        = 0x2A, 
    instrMulF32        = 0x2B, 
    instrMulF64        = 0x2C, 

    instrDivI32        = 0x2D, 
    instrDivI64        = 0x2E, 
    instrDivF32        = 0x2F, 
    instrDivF64        = 0x30, 
    instrDivU32        = 0x31, 
    instrDivU64        = 0x32, 

    instrModI32        = 0x33, 
    instrModU32        = 0x34, 
    instrModI64        = 0x35, 
    instrModU64        = 0x36, 

    instrLogicAnd      = 0x37, 
    instrLogicOr       = 0x38, 
    instrLogicNot      = 0x39, 
    instrLogicXor      = 0x3A, 

    instrBitAnd        = 0x3B, 
    instrBitOr         = 0x3C, 
    instrBitNot        = 0x3D, 
    instrBitXor        = 0x3E, 

    instrBitLShift     = 0x3F, 
    instrBitRShift     = 0x40, 
    instrBitRaShift    = 0x41, 
    instrBitRShift32   = 0x42, 
    instrBitRaShift32  = 0x43, 

    instrCmpI32        = 0x44, 
    instrCmpI64        = 0x45, 
    instrCmpF32        = 0x46, 
    instrCmpF64        = 0x47, 

    instrCmp2BoolEq    = 0x48, 
    instrCmp2BoolNe    = 0x49, 
    instrCmp2BoolLt    = 0x4A, 
    instrCmp2BoolLe    = 0x4B, 
    instrCmp2BoolGt    = 0x4C, 
    instrCmp2BoolGe    = 0x4D, 

    instrF32I32        = 0x4E, 
    instrI32F32        = 0x4F, 
    instrI64F64        = 0x50, 
    instrF64I64        = 0x51, 
    instrF32F64        = 0x52, 
    instrF64F32        = 0x53, 
    instrI32I64        = 0x54, 
    instrI64I32        = 0x55, 

    instrJmp           = 0x56, 
    instrJmpTrue       = 0x57, 
    instrJmpFalse      = 0x58, 

    instrFuncCall      = 0x59, 
    instrReturn        = 0x5A, 

    instrConNew        = 0x5B, 
    instrConDel        = 0x5C, 
    instrConStore      = 0x5D, 
    instrConGStore     = 0x5E, 
    instrConLoad       = 0x5F, 
    instrConGLoad      = 0x60, 
    instrConCopy       = 0x61, 
    instrConClone      = 0x62, 
    instrConAccLoad    = 0x63, 
    instrConAccStore   = 0x64, 
    instrConInc        = 0x65, 
    instrConDec        = 0x66

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