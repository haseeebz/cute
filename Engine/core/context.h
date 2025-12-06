#include "CuteByte.h"
#include "CuteAtom.h"
#include "CuteConfig.h"
#include "error.h"

#pragma once


typedef struct
{
	ctAtom atoms[CUTE_EXESTACK_LIMIT];
	uint32_t count;
	uint32_t cap;
} ctExeStack;


typedef struct 
{
	uint32_t return_address;
	uint32_t locals_count;
	ctAtom *locals;
} ctFuncFrame;

typedef struct
{
	ctFuncFrame frames[CUTE_FUNCSTACK_LIMIT];
	uint32_t count;
	uint32_t cap;
} ctFuncStack;


typedef struct
{
	ctExeStack exestack;
	ctFuncStack funcstack;

	// Do not free these, owned by the engine
	ctProgramImage* img;
	ctFuncMetadata* func_table;

	uint64_t pc;

	bool is_running;
	bool error_encountered;

	ctError error;
} ctContext;


void ctx_init(ctContext *ctx, ctProgramImage *img);
void ctx_end(ctContext *ctx);

void ctx_pushExeAtom(ctContext *ctx, ctAtom atom);
ctAtom ctx_popExeAtom(ctContext *ctx);
ctAtom ctx_peekExeAtom(ctContext *ctx);

void ctx_storeLocal(ctContext *ctx, uint32_t pos, ctAtom atom);
ctAtom ctx_loadLocal(ctContext *ctx, uint32_t pos);
void ctx_copyLocal(ctContext *ctx, uint32_t src, uint dest);

void ctx_funcCall(ctContext *ctx, uint32_t func_id);
void ctx_funcReturn(ctContext *ctx);

void ctx_raiseError(ctContext *ctx);