#include <stdio.h>
#include "../Bytecode/include/instr.h"
#include "../Bytecode/include/loader.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

    
int main()
{

	ProgramContext* ctx = ProgramContext_new();
	
	ProgramContext_addInstruction(ctx, instrLCONi);
	ProgramContext_addInt(ctx, 10);
	ProgramContext_addInstruction(ctx, instrLCONi);
	ProgramContext_addInt(ctx, 20);
	ProgramContext_addInstruction(ctx, instrADDi);
	ProgramContext_addInstruction(ctx, instrOUT);
	ProgramContext_addInstruction(ctx, instrEXIT);


	ProgramContext_writeToFile(ctx, "file.bin");
	ProgramContext_print(ctx);

	
	ProgramContext_loadFromFile(ctx, "file.bin");
	ProgramContext_print(ctx);

	ProgramContext_del(ctx);
	return 0;
}