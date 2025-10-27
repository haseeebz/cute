#include "include/CuteByte.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void ProgramContext_init(ProgramContext* ctx, size_t capacity)
{
    ctx->instr_cap = capacity;
    ctx->instr_count = 0;
    ctx->instrs = malloc(sizeof(CtInstrSize) * capacity);
}


void ProgramContext_end(ProgramContext* ctx)
{
    free(ctx->instrs);
    ctx->instr_cap = 0;
    ctx->instr_count = 0;
}


void ProgramContext_read(ProgramContext* ctx, char* filepath)
{
    FILE* fp = fopen(filepath, "rb");

    if (!fp) {printf("ERROR: File could not be opened for reading.\n"); exit(EXIT_FAILURE);}

    size_t count;
    fread(&count, sizeof(size_t), 1, fp);

    ProgramContext_init(ctx, count);
    ctx->instr_count = count;

    fread(ctx->instrs, sizeof(CtInstrSize), ctx->instr_count, fp);

    printf("Instr Count: %d\n", ctx->instr_count);

    for (int i = 0; i < ctx->instr_count; i++)
    {
        printf("Read instruction: %X\n", ctx->instrs[i]);
    }


    fclose(fp);
}


void ProgramContext_write(ProgramContext* ctx, char* filepath)
{
    FILE* fp = fopen(filepath, "wb");

    if (!fp) {printf("ERROR: File could not be opened for writing.\n"); exit(EXIT_FAILURE);}

    fwrite(&ctx->instr_count, sizeof(size_t), 1, fp);
    fwrite(ctx->instrs, sizeof(CtInstrSize), ctx->instr_count, fp);

    for (int i = 0; i < ctx->instr_count; i++)
    {
        printf("Wrote instruction: %X\n", ctx->instrs[i]);
    }

    fclose(fp);
}