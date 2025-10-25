#include "exe/cell.h"
#include "include/CuteEngine.h"
#include "CuteByte.h"

#include "exe/stack.h"
#include <stdint.h>
#include <stdio.h>


void CuteEngine_init(CuteEngine *engine)
{
    ExeStack_init(&engine->stack, 8);
    engine->pc = 0;

    CtInstr instrs[] = {
        instrPushConstI,1000000000,
        instrPushConstI,0,
        instrStation, 0,
        instrPushConstI, 1,
        instrAddI,
        instrOutI,
        instrJmpE, 0,
        instrHalt,
    };

    for (int i = 0; i < sizeof(instrs)/sizeof(CtInstr); i++)
    {
        engine->instrs[i] = instrs[i];
    }
}


void CuteEngine_run(CuteEngine *engine)
{
    CtInstr instr;
    int32_t i1;
    int32_t i2;

    while (1)
    {
        instr = engine->instrs[engine->pc++];

        switch (instr) 
        {
        
        case instrHalt:
            printf("Halting the engine.\n");
            return;

        case instrPushConstI:
            i1 = engine->instrs[engine->pc++];
            ExeStack_push(&engine->stack, (CuteCell) {.val.i = i1});
            break;

        case instrAddI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (CuteCell) {.val.i = i1 + i2});
            break;

        case instrSubI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (CuteCell) {.val.i = i1 - i2});
            break;

        case instrMulI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (CuteCell) {.val.i = i1 * i2});
            break;

        case instrDivI:
            i2 = ExeStack_pop(&engine->stack).val.i;
            i1 = ExeStack_pop(&engine->stack).val.i;
            ExeStack_push(&engine->stack, (CuteCell) {.val.i = i1 / i2});
            break;

        case instrOutI:
            i1 = ExeStack_peek(&engine->stack)->val.i;
            printf("%d\n", i1);
            break;


        case instrStation:
            i1 = engine->instrs[engine->pc++];
            engine->stations[i1] = engine->pc;
            break;

        case instrJmpE:
            i2 = ExeStack_peek(&engine->stack)->val.i;
            i1 = engine->stack.obj[engine->stack.count-2].val.i;
            ExeStack_push(&engine->stack, (CuteCell) {.val.i = (i1 == i2 ? 1 : 0)});
            i2 = engine->instrs[engine->pc++];
            i1 = ExeStack_pop(&engine->stack).val.i;
            if (!i1)
            {
                engine->pc = engine->stations[i2];
            }
            break;
        }
    }
}


void CuteEngine_end(CuteEngine *engine)
{
    ExeStack_end(&engine->stack);
}