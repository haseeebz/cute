
#include "include/CuteEngine.h"
#include "CuteByte.h"

#include "CuteAtom.h"
#include "exe/stack.h"

#include <stdint.h>
#include <stdio.h>


void CuteEngine_init(CuteEngine *engine)
{
    ExeStack_init(&engine->stack, 8);

    engine->pc = 0;

	ProgramContext ctx;
    ProgramContext_read(&ctx, "file.bin");
    engine->ctx = ctx;
}


void CuteEngine_run(CuteEngine *engine)
{
    CtInstrSize *instrs = engine->ctx.instrs;
    CtInstr instr;
    int32_t i1;
    int32_t i2;

    while (1)
    {
        instr = (CtInstr) instrs[engine->pc++];

        switch (instr) 
        {
        
        case instrHalt:
            printf("Halting the engine.\n");
            return;

        case instrPushConstI:
            i1 = instrs[engine->pc++];
            ExeStack_push(&engine->stack, (ctAtom) {.val.i = i1});
            break;


        case instrAddI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (ctAtom) {.val.i = i1 + i2});
            break;

        case instrSubI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (ctAtom) {.val.i = i1 - i2});
            break;

        case instrMulI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (ctAtom) {.val.i = i1 * i2});
            break;

        case instrDivI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (ctAtom) {.val.i = i1 / i2});
            break;

        case instrOutI:
            i1 = ExeStack_peek(&engine->stack)->val.i;
            printf("%d\n", i1);
            break;

        }
    }
}


void CuteEngine_end(CuteEngine *engine)
{
    ExeStack_end(&engine->stack);
    ProgramContext_end(&engine->ctx);
}