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

	instrExitEngine = 0, 
	instrExit = 1, 
	instrOut = 2, 
	instrDump = 3, 
	instrPopAtom = 4, 
	instrDupAtom = 5, 
	instrNull = 6, 
	instrModCall = 7, 

	instrLoadCoI32 = 8, 
	instrLoadCoI64 = 9, 
	instrLoadCoF32 = 10, 
	instrLoadCoF64 = 11, 
	instrLoadConst = 12, 

	instrLoadI32 = 13, 
	instrLoadI64 = 14, 
	instrLoadF32 = 15, 
	instrLoadF64 = 16, 

	instrGLoadI32 = 17, 
	instrGLoadI64 = 18, 
	instrGLoadF32 = 19, 
	instrGLoadF64 = 20, 

	instrStoreI32 = 21, 
	instrStoreI64 = 22, 
	instrStoreF32 = 23, 
	instrStoreF64 = 24, 

	instrGStoreI32 = 25, 
	instrGStoreI64 = 26, 
	instrGStoreF32 = 27, 
	instrGStoreF64 = 28,

	instrCopyI32 = 29, 
	instrCopyI64 = 30, 
	instrCopyF32 = 31, 
	instrCopyF64 = 32, 

	instrAddI32 = 33, 
	instrAddI64 = 34, 
	instrAddF32 = 35, 
	instrAddF64 = 36, 

	instrSubI32 = 37, 
	instrSubI64 = 38, 
	instrSubF32 = 39, 
	instrSubF64 = 40, 

	instrMulI32 = 41, 
	instrMulI64 = 42, 
	instrMulF32 = 43, 
	instrMulF64 = 44, 

	instrDivI32 = 45, 
	instrDivI64 = 46, 
	instrDivF32 = 47, 
	instrDivF64 = 48, 
	instrDivU32 = 49, 
	instrDivU64 = 50, 

	instrModI32 = 51, 
	instrModU32 = 52, 
	instrModI64 = 53, 
	instrModU64 = 54, 

	instrLogicAnd = 55, 
	instrLogicOr = 56, 
	instrLogicNot = 57, 
	instrLogicXor = 58, 

	instrBitAnd = 59, 
	instrBitOr = 60, 
	instrBitNot = 61, 
	instrBitXor = 62, 

	instrBitLShift = 63, 
	instrBitRShift = 64, 
	instrBitRaShift = 65, 
	instrBitRShift32 = 66, 
	instrBitRaShift32 = 67, 

	instrCmpI32 = 68, 
	instrCmpI64 = 69, 
	instrCmpF32 = 70, 
	instrCmpF64 = 71, 

	instrCmp2BoolEq = 72, 
	instrCmp2BoolNe = 73, 
	instrCmp2BoolLt = 74, 
	instrCmp2BoolLe = 75, 
	instrCmp2BoolGt = 76, 
	instrCmp2BoolGe = 77, 

	instrF32I32 = 78, 
	instrI32F32 = 79, 
	instrI64F64 = 80, 
	instrF64I64 = 81, 
	instrF32F64 = 82, 
	instrF64F32 = 83, 
	instrI32I64 = 84, 
	instrI64I32 = 85, 

	instrJmp = 86, 
	instrJmpTrue = 87, 
	instrJmpFalse = 88, 

	instrFuncCall = 89, 
	instrReturn = 90, 
	
	instrConNew = 91, 
	instrConDel = 92, 
	instrConStore = 93, 
	instrConGStore = 94, 
	instrConLoad = 95, 
	instrConGLoad = 96, 
	instrConCopy = 97, 
	isntrConClone = 98, 
	instrConAccLoad = 99, 
	instrConAccStore = 100, 
	instrConInc = 101, 
	instrConDec = 102, 


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
	
	uint32_t const_pool_offset;
	uint32_t const_count;

	uint32_t func_table_offset;
	uint32_t func_count;

	uint32_t instr_blob_offset;
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

inline void ctProgramImage_packInt32(int32_t *i, ctInstrSize *instr4); 
inline void ctProgramImage_packInt64(int64_t *i, ctInstrSize *instr8); 
inline void ctProgramImage_packFloat32(float *i, ctInstrSize *instr4); 
inline void ctProgramImage_packFloat64(double *i, ctInstrSize *instr8); 


#ifdef __cplusplus
}
#endif