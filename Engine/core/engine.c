#include "CuteEngine.h"
#include "CuteByte.h"

#include <stdio.h>
#include <stdlib.h>

#include "../core/context.h"

// The main engine struct
ctEngine engine;


void ctEngine_init()
{
	
};

// Ends the Engine and all its states
void ctEngine_end(int exit_code)
{
	exit(exit_code);
}



// Sets up state struct with function 0 and executes it.
void ctEngine_run()
{
	ctContext ctx;
	ctx_init(&ctx, &engine.img);
	ctx_funcCall(&ctx, 0);
	ctEngine_exec(&ctx);
	ctEngine_end(0);
}


// Loading an image file
void ctEngine_loadImage(char *filepath)
{
	ctImageError code = ctProgramImage_read(&engine.img, filepath);
	
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

		ctEngine_end(1);
	}

}

