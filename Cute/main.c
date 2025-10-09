#include <stdio.h>
#include "../engine/include/engine.h"


int main()
{
	CuteEngine* engine = CuteEngine_setup("file.bin");

	OpCode codes[] = 
	{
		opLCONi, 
		1,
		opSTORi,
		0,
		opLOADi,
		0,
		opLCONi,
		2,
		opADDi,
		opSTORi,
		0,
		opOUT,
		opLCONi,
		128,
		opEQi,
		opJMPe,
		4,
		opEXIT
	};

	CuteEngine_write(engine, codes, sizeof(codes)/sizeof(OpCode));
	CuteEngine_load(engine);
	CuteEngine_run(engine);
	CuteEngine_end(engine);
	return 0;
}