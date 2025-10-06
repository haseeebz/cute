#include <stdio.h>
#include "../engine/include/engine.h"


int main()
{
	CuteEngine* engine = CuteEngine_setup("file.bin");

	OpCode codes[] = 
	{
		opLOADi, 1, 10,
		opLOADi, 2, 10,
		opADDi, 0, 1, 2,

		opSTRi, 0, 0,
		opREADi, 5, 0,
		opOUT, 5,
		opEXIT
	};

	CuteEngine_write(engine, codes, sizeof(codes));
	CuteEngine_load(engine);
	CuteEngine_run(engine);
	CuteEngine_end(engine);
	return 0;
}