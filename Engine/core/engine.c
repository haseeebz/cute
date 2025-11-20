#include "CuteByte.h"
#include "CuteEngine.h"
#include "../state/state.h"
#include <stdio.h>
#include <stdlib.h>


CuteEngine ctEngine;

void CuteEngine_init()
{
	return;
}


void CuteEngine_end()
{
	exit(EXIT_SUCCESS);
}


void CuteEngine_loadImage(char* filepath)
{
	ctImageError code = ctProgramImage_read(&ctEngine.img, filepath);

	if (code != ctImageError_Success)
	{
		if (code == ctImageError_ByteReadFailure)
		{
			printf("Image file could be not be read: %s\n", filepath);
			CuteEngine_end();
		}
		else if (code == ctImageError_FileNotFound)
		{
			printf("Image file not found: %s\n", filepath);
			CuteEngine_end();
		}
	}
}


void CuteEngine_runMain()
{
	CtState state;
	CtState_init(&state, &ctEngine.img);
	
	CuteEngine_execLoop(&state);

	CtState_end(&state);

	CuteEngine_end();
}
