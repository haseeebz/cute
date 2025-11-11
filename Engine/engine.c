#include "CuteByte.h"
#include "CuteEngine.h"
#include "context/context.h"
#include <stdio.h>
#include <stdlib.h>


CuteEngine ctEngine;

void CuteEngine_init()
{
	return;
}


void CuteEngine_end()
{
	exit(EXIT_FAILURE);
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


CtContext* CuteEngine_newContext()
{
	CtContext* ctx = malloc(sizeof(CtContext));
	ctx->img = &ctEngine.img;
	ctx->pc = 0;

	return ctx;
}

void CuteEngine_endContext(CtContext** ctx)
{
	free(ctx);
	ctx = NULL;
}


void CuteEngine_runMain()
{
	CtContext* ctx = CuteEngine_newContext();
	
	CuteEngine_execLoop(ctx);

	CuteEngine_endContext(&ctx);
}


void CuteEngine_execLoop(CtContext* ctx);


