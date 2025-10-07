#include <stdio.h>
#include "../engine/include/engine.h"


int main()
{
	CuteEngine* engine = CuteEngine_setup("file.bin");

	OpCode codes[] = 
	{
		opLOADi, 
		10,
		opLOADi,
		2,
		opMULi,
		opLOADi, 
		10,
		opADDi,
		opLOADi,
		30,
		opSUBi,
		opOUT,
		opEXIT
	};

	CuteEngine_write(engine, codes, sizeof(codes));
	CuteEngine_load(engine);
	CuteEngine_run(engine);
	CuteEngine_end(engine);
	return 0;
}