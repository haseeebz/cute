#include "CuteLib.h"

typedef struct 
{
	cute_U32 refcount;
	void (*destructor)();
}
cute_Container;


typedef struct
{
	cute_Container* containers[10];
}
cute_ContainerManager;


void
cute_ContainerManager_init();

void
cute_ContainerManager_end();

cute_Container* 
cute_ContainerManager_new(size_t size);

void 
cute_ContainerManager_del(cute_Container* container);