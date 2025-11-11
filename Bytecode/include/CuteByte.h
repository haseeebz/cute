#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


#pragma once
 
#ifdef __cplusplus
extern "C" {
#endif

// probably important
typedef uint8_t ctInstrSize;


// main instruction set

typedef enum
{
    instrHalt            = 0x00,

    instrDupAtom         = 0x01,
    instrPopAtom         = 0x02,

    instrLoadCoI8        = 0x03,
    instrLoadCoI32       = 0x04,
    instrLoadCoI64       = 0x05,
    instrLoadCoF32       = 0x06,
    instrLoadCoF64       = 0x07,

    instrLoadI32         = 0x08,
    instrLoadI64         = 0x09,
    instrLoadF32         = 0x0A,
    instrLoadF64         = 0x0B,

    instrStoreI32        = 0x0C,
    instrStoreI64        = 0x0D,
    instrStoreF32        = 0x0E,
    instrStoreF64        = 0x0F,

    instrAddI32          = 0x10,
    instrAddI64          = 0x11,
    instrAddF32          = 0x12,
    instrAddF64          = 0x13,

    instrSubI32          = 0x14,
    instrSubI64          = 0x15,
    instrSubF32          = 0x16,
    instrSubF64          = 0x17,

    instrMulI32          = 0x18,
    instrMulI64          = 0x19,
    instrMulF32          = 0x1A,
    instrMulF64          = 0x1B,

    instrDivI32          = 0x1C,
    instrDivI64          = 0x1D,
    instrDivF32          = 0x1E,
    instrDivF64          = 0x1F,

    instrAnd             = 0x20,
    instrOr              = 0x21,
    instrNot             = 0x22,
    instrXor             = 0x23,

    instrCmpI32          = 0x24,
    instrCmpI64          = 0x25,
    instrCmpF32          = 0x26,
    instrCmpF64          = 0x27,

    instrCmp2BoolEq      = 0x28,
    instrCmp2BoolNe      = 0x29,
    instrCmp2BoolLt      = 0x2A,
    instrCmp2BoolLe      = 0x2B,
    instrCmp2BoolGt      = 0x2C,
    instrCmp2BoolGe      = 0x2D,

    instrJmp             = 0x2E,
    instrJmpTrue         = 0x2F,
    instrJmpFalse        = 0x30,

    instrCall            = 0x31,
    instrCallVirtual     = 0x32,
    instrReturn          = 0x33,

    // Future expansion
    instrNewCon          = 0x34,
    instrAccessCon       = 0x35,
    instrDelCon          = 0x36,

	instrOut             = 0x37,

} ctInstr;



// program image defs

typedef struct
{
	union
	{
		int64_t i64;
		int32_t i32;
		float 	f32;
		double  f64;
	};

} Constant;


typedef struct
{
	u_int32_t magic;
	u_int32_t const_count;
	u_int32_t instr_count;
} ctProgramHeader;

typedef struct
{
	ctProgramHeader header;
	Constant* consts;
	ctInstrSize* instrs;
} ctProgramImage;


// to make error handling easier

typedef enum
{

	ctImageError_Success = 0x00,
	ctImageError_FileNotFound = 0x01,
	ctImageError_ByteReadFailure = 0x02,
	ctImageError_ByteWriteFailure = 0x03,

} ctImageError;

void ctProgramImage_free(ctProgramImage* img);
ctImageError ctProgramImage_read(ctProgramImage* img, char* filepath);
ctImageError ctProgramImage_write(ctProgramImage* img, char* filepath);


u_int32_t ctProgramImage_addConstant(Constant const);


#ifdef __cplusplus
}
#endif