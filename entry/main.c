#include "CuteLib.h"
#include "CuteContainer.h"
#include <stdio.h>


void program_main()
{
	cute_Container* con = cute_ContainerManager_new(sizeof(cute_Container));
	printf("hello!\n");
	con->refcount = 0;
}

int main()
{
	cute_Core_run(program_main);
};