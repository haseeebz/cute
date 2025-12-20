#include "CuteEngine.h"
#include "CuteByte.h"

#include <stdio.h>
#include <stdlib.h>

#include "../core/context.h"

// The main engine struct
CuteEngine ctEngine;


void CuteEngine_init()
{
	
};

// Ends the Engine and all its states
void CuteEngine_end(int exit_code)
{
	exit(exit_code);
}



// Sets up state struct with function 0 and executes it.
void CuteEngine_run()
{
	ctContext ctx;
	ctx_init(&ctx, &ctEngine.img);
	ctx_funcCall(&ctx, 0);
	CuteEngine_exec(&ctx);
	CuteEngine_end(0);
}


// Loading an image file
void CuteEngine_loadImage(char *filepath)
{
	ctImageError code = ctProgramImage_read(&ctEngine.img, filepath);
	
	if (code != ctImageError_Success)
	{

		if (code == ctImageError_ReadWriteFailure)
		{
			printf("Image file could be not be read: %s\n", filepath);
		}
		else if (code == ctImageError_FileNotFound)
		{
			printf("Image file not found: %s\n", filepath);
		}
		else if (code == ctImageError_InvalidImage)
		{
			printf("Invalid Image file: %s\n", filepath);
		}

		CuteEngine_end(1);
	}

}

