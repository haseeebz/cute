
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
    
}


void CuteEngine_run(CuteEngine *engine, char* filepath)
{
	ctProgramImage_read(&engine->img, filepath);

    ctInstrSize *instrs = engine->img.instrs;
    ctInstr instr;
    int64_t i1;
    int64_t i2;

    while (1)
    {
        instr = (ctInstr) instrs[engine->pc++];

        switch (instr) 
        {
        
        case instrHalt:
            printf("Halting the engine.\n");
            return;

        case instrLoadCoI:
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
            printf("%ld\n", i1);
            break;

        }
    }
}


void CuteEngine_end(CuteEngine *engine)
{
    ExeStack_end(&engine->stack);
    ctProgramImage_free(&engine->img);
}