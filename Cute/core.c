#include "CuteLib.h"
#include "CuteContainer.h"
#include <stdio.h>

static struct cute_Core CuteCore;

void cute_Core_run(void (*main)())
{
	CuteCore.main = main;

	cute_Core_init();
	cute_ContainerManager_init();

	CuteCore.main();

	cute_ContainerManager_end();
	cute_Core_end();
}

void cute_Core_init()
{
	printf("Starting cute...\n");
};

void cute_Core_end()
{
	printf("Ending cute...\n");
}

