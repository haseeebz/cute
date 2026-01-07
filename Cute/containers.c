#include "CuteLib.h"
#include "CuteContainer.h"
#include <stdio.h>


static cute_ContainerManager CuteContainerManager;

void
cute_ContainerManager_init()
{
}

void
cute_ContainerManager_end()
{
	for (cute_U32 i = 0; i < 10; i++)
	{
		cute_Container* con = CuteContainerManager.containers[i];

		if (con != NULL)
		{
			printf("Freed container : %p\n", con);
			free(con);
		}
	}
}

cute_Container* 
cute_ContainerManager_new(size_t size)
{
	for (cute_U32 i = 0; i < 10; i++)
	{
		cute_Container* con = CuteContainerManager.containers[i];

		if (con == NULL)
		{
			con = malloc(size);
			CuteContainerManager.containers[i] = con;

			printf("Allocated container : %p\n", con);
			return con;
		}

		if (con->refcount == 0)
		{
			free(con);
			printf("Freed container : %p\n", con);
			con = malloc(size);
			CuteContainerManager.containers[i] = con;
			printf("Allocated container : %p\n", con);
			return con;
		}
	}

	printf("Memory Full!\n");

	return NULL;
}
