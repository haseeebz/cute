#include "include/CuteByte.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void ProgramContext_init(ProgramContext* ctx, CtInstrSize* instrs, size_t count)
{
    ctx->instr_count = count;
    ctx->instrs = instrs;
}


void ProgramContext_end(ProgramContext* ctx)
{
    free(ctx->instrs);
    ctx->instr_count = 0;
}


void ProgramContext_read(ProgramContext* ctx, char* filepath)
{
    FILE* fp = fopen(filepath, "rb");

    if (!fp) {printf("ERROR: File could not be opened for reading.\n"); exit(EXIT_FAILURE);}

    fread(&ctx->instr_count, sizeof(size_t), 1, fp);
    fread(ctx->instrs, sizeof(CtInstrSize), ctx->instr_count, fp);

    fclose(fp);
}


void ProgramContext_write(ProgramContext* ctx, char* filepath)
{
    FILE* fp = fopen(filepath, "wb");

    if (!fp) {printf("ERROR: File could not be opened for writing.\n"); exit(EXIT_FAILURE);}

    fwrite(&ctx->instr_count, sizeof(size_t), 1, fp);
    fwrite(ctx->instrs, sizeof(CtInstrSize), ctx->instr_count, fp);

    fclose(fp);
}