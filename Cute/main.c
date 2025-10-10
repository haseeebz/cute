#include <stdio.h>
#include "../Bytecode/include/instr.h"
#include "../Bytecode/include/loader.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



void print_constant(ConstantValue* c, size_t index) {
    printf("  [%zu] Type: ", index);
    switch (c->type) {
        case constInt:
            printf("Int | Value: %d\n", c->val.i);
            break;
        case constDouble:
            printf("Double | Value: %lf\n", c->val.d);
            break;
        default:
            printf("Unknown Type (%d)\n", c->type);
            break;
    }
}

// Utility to print the full context
void print_program_context(const ProgramContext* ctx) {
    printf("=== ProgramContext Dump ===\n");
    printf("Header:\n");
    printf("  Magic: %d\n", ctx->header.magic);
    printf("  Constant Pool Index: %d\n", ctx->header.constant_pool_index);
    printf("  Constant Count (Header): %d\n", ctx->header.constant_count);
    printf("  Instructions Index: %d\n", ctx->header.instructions_index);
    printf("  Instruction Count (Header): %d\n", ctx->header.instr_count);

    printf("\nConstant Pool (Count: %zu, Capacity: %zu)\n", ctx->const_count, ctx->_const_cap);
    for (size_t i = 0; i < ctx->const_count; i++) {
        print_constant(&ctx->constant_pool[i], i);
    }

    printf("\nInstructions (Count: %zu, Capacity: %zu)\n", ctx->instr_count, ctx->_instr_cap);
    for (size_t i = 0; i < ctx->instr_count; i++) {
        printf("  [%zu] Opcode: %d\n", i, ctx->instrs[i]);
    }
}

  

int main()
{
	ProgramContext* context = ProgramContext_new();
	int codes;
	ConstantValue value = {constInt, {.i = 10}};
	codes = ProgramContext_addConstant(context, value);

	ConstantValue value2 = {constDouble, {.d = 24.3}};
	codes = ProgramContext_addConstant(context, value2);

	ProgramContext_addInstruction(context, instrADDi);
	ProgramContext_addInstruction(context, instrEXIT);

	ProgramContext_writeToFile(context, "~/Code/cute/build/test.bin");
	print_program_context(context);
	ProgramContext_del(context);


	return 0;
}