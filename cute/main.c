#include "engine/engine.h"
#include <stdio.h>

int main()
{
	CuteEngine* engine = CuteEngine_setup("file.bin");

	OpCode codes[] = {10, 9, 7, 10};
	CuteEngine_write(engine, codes, 3);

	OpCode* file_codes = CuteEngine_load(engine);
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", file_codes[i]);
	}
	CuteEngine_end(engine);
	return 0;
}