#include <stdio.h>
#include "../engine/include/engine.h"


int main()
{
	CuteEngine* engine = CuteEngine_setup("file.bin");

	OpCode codes[] = 
	{
		opLCONi, 
		64,
		opLCONi, 
		32,
		opSTORi,
		0,
		opLOADi,
		0,
		opOUT,
		opEXIT
	};

	CuteEngine_write(engine, codes, sizeof(codes)/sizeof(OpCode));
	CuteEngine_load(engine);
	CuteEngine_run(engine);
	CuteEngine_end(engine);
	return 0;
}