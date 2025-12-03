#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


#pragma once
 
#ifdef __cplusplus
extern "C" {
#endif

static const uint32_t ctMagicId = 0x20080807;


// probably important
typedef uint8_t ctInstrSize;


// main instr set

typedef enum
{

	// Control / special
	instrHalt            = 0x00,  // 0

	// Atom operations
	instrPopAtom         = 0x01,
	instrDupAtom         = 0x02,

	instrLoadCoI32       = 0x03,
	instrLoadCoI64       = 0x04,
	instrLoadCoF32       = 0x05,
	instrLoadCoF64       = 0x06,

	instrLoadI32         = 0x07,
	instrLoadI64         = 0x08,
	instrLoadF32         = 0x09,
	instrLoadF64         = 0x0A,

	instrStoreI32        = 0x0B,
	instrStoreI64        = 0x0C,
	instrStoreF32        = 0x0D,
	instrStoreF64        = 0x0E,

	instrCopyI32         = 0x0F,
	instrCopyI64         = 0x10,
	instrCopyF32         = 0x11,
	instrCopyF64         = 0x12,

	// Arithmetic operations
	instrAddI32          = 0x13,
	instrAddI64          = 0x14,
	instrAddF32          = 0x15,
	instrAddF64          = 0x16,

	instrSubI32          = 0x17,
	instrSubI64          = 0x18,
	instrSubF32          = 0x19,
	instrSubF64          = 0x1A,

	instrMulI32          = 0x1B,
	instrMulI64          = 0x1C,
	instrMulF32          = 0x1D,
	instrMulF64          = 0x1E,

	instrDivI32          = 0x1F,
	instrDivI64          = 0x20,
	instrDivF32          = 0x21,
	instrDivF64          = 0x22,

	// Logic operations
	instrLogicAnd        = 0x23,
	instrLogicOr         = 0x24,
	instrLogicNot        = 0x25,

	// Comparison operations
	instrCmpI32          = 0x27,
	instrCmpI64          = 0x28,
	instrCmpF32          = 0x29,
	instrCmpF64          = 0x2A,

	instrCmp2BoolEq      = 0x2B,
	instrCmp2BoolNe      = 0x2C,
	instrCmp2BoolLt      = 0x2D,
	instrCmp2BoolLe      = 0x2E,
	instrCmp2BoolGt      = 0x2F,
	instrCmp2BoolGe      = 0x30,

	// Control flow
	instrJmpA            = 0x31, // absolute jump
	instrJmp             = 0x32, // relative jumps
	instrJmpTrue         = 0x33,
	instrJmpFalse        = 0x34,

	instrFuncCall        = 0x35,
	instrReturn          = 0x36,
	instrReturnValue     = 0x37,

	instrOutI32 = 0x41,
	instrOutI64 = 0x42,
	instrOutF32 = 0x43,
	instrOutF64 = 0x44,


} ctInstr;


/*
Program Image Defs
*/

// Sections

typedef enum
{
	constI32 = 0, 
	constI64 = 1, 
	constF32 = 2, 
	constF64 = 3, 
	constString = 4
} ctProgramConstType;

typedef uint8_t ctProgramConstTSize;

typedef struct
{
	union
	{
		int64_t i64;
		int32_t i32;
		float 	f32;
		double  f64;
	};

} ctProgramConst;


typedef struct
{

	uint32_t func_id;
	uint16_t arg_count;
	uint16_t locals_size;
	uint64_t instr_address;

} ctFuncMetadata;


// Main

typedef struct
{
	u_int32_t magic;
	u_int32_t const_count;
	u_int32_t func_count;
	u_int32_t instr_count;
	
} ctProgramHeader;


typedef struct
{
	ctProgramHeader header;

	ctProgramConstTSize *const_type_table;
	ctProgramConst *const_table;

	ctFuncMetadata *func_table;
	ctInstrSize *instrs;

} ctProgramImage;


// to make error handling easier

typedef enum
{
	ctImageError_Success = 0x00,
	ctImageError_FileNotFound = 0x01,
	ctImageError_ByteReadWriteFailure = 0x02,
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