#include "include/CuteEngine.h"
#include "include/CuteInstr.h"

#include "exe.h"
#include <stdio.h>


void CuteEngine_init(CuteEngine *engine)
{
    ExeStack_init(&engine->stack, 8);
    engine->pc = 0;

    Instr instrs[] = {

        instrHalt,
    };

    for (int i = 0; i < sizeof(instrs)/sizeof(Instr); i++)
    {
        engine->instrs[i] = instrs[i];
    }
}


void CuteEngine_run(CuteEngine *engine)
{
    Instr instr;

    while (1)
    {
        instr = engine->instrs[engine->pc++];

        switch (instr) 
        {
        
        case instrHalt:
            printf("Halting the engine.\n");
            return;
            
        }
    }
}


void CuteEngine_end(CuteEngine *engine)
{
    ExeStack_end(&engine->stack);
}