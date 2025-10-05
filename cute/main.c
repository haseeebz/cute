#include <stdio.h>
#include "../engine/include/engine.h"


int main()
{
	CuteEngine* engine = CuteEngine_setup("file.bin");

	OpCode codes[] = 
	{
		opLOADi, 0, 120,
		opLOADi, 1, 100,
		opADDi, 0, 1, 2,
		opOUT, 2,
		opHALT
	};

	//CuteEngine_write(engine, codes, sizeof(codes));

	CuteEngine_load(engine);
	CuteEngine_run(engine);
	
	CuteEngine_end(engine);
	return 0;
}