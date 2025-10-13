#include "cuteByte.h"
    
int main()
{
	ProgramSource* program = ProgramSource_new();
	

	ProgramSource_addInstruction(program, instrLOADi);
	ProgramSource_addInstruction(program, instrLOADi);
	ProgramSource_addInstruction(program, instrSTORi);
	ProgramSource_addInstruction(program, instrLCONi);
	ProgramSource_addInstruction(program, instrEXIT);
	
	ProgramSource_writeToFile(program, "file.bin");

	ProgramSource_loadFromFile(program, "file.bin");
	ProgramSource_print(program);

	ProgramSource_del(program);

	return 0;
}