#include <stdio.h>

#include "CuteLib.h"
#include "CuteContainer.h"

#include "../internal/logs.h"


static struct cute_Core CuteCore;


void cute_Core_run(void (*main)())
{
	CuteCore.main = main;

	cute_Core_init();

	logs_logMessage(
		"core",
		logs_level_info,
		"running 'main'"		
	);

	CuteCore.main();

	logs_logMessage(
		"core",
		logs_level_info,
		"'main' finished successfully"		
	);

	cute_Core_end();
}


void cute_Core_init()
{
	logs_logMessage(
		"core",
		logs_level_info,
		"Hello, World!"		
	);

	logs_logMessage(
		"core",
		logs_level_debug,
		"function 'main' specified. Is %p", CuteCore.main	
	);

	cute_ContainerManager_init();
};


void cute_Core_end()
{
	cute_ContainerManager_end();

	logs_logMessage(
		"core",
		logs_level_info,
		"Ending cute..."		
	);
}


void cute_Core_exit(cute_ExitCode code)
{
	logs_logMessage(
		"core",
		logs_level_info,
		"Explictly calling 'exit' with code %d", code		
	);

	cute_Core_end();
	exit(code);
}
