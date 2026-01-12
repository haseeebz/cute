#include "CuteLib.h"
#include "CuteContainer.h"
#include <stdio.h>


static cute_ContainerManager Manager;

inline static cute_ContainerBucket* 
cute_Bucket_new() 
{
    cute_ContainerBucket* self = malloc(sizeof(cute_ContainerBucket));
    self->size = 0;
    self->capacity = 0;
    printf("[Bucket New] Bucket %p created\n", (void*)self);
    return self;
}

inline static void 
cute_Bucket_del(cute_ContainerBucket* self) 
{
    printf("[Bucket Delete] Bucket %p deleted\n", (void*)self);
    free(self->containers);
    self->containers = NULL;
    self->size = self->capacity = 0;
}

inline static int 
cute_Bucket_push(cute_ContainerBucket* self, cute_Container* c) 
{
    if (self->size >= self->capacity) 
    {
        size_t new_cap = self->capacity ? self->capacity * 2 : 4;
        cute_Container** tmp = (cute_Container**)realloc(self->containers, sizeof(cute_Container*) * new_cap);
        if (!tmp) return 0;
        self->containers = tmp;
        self->capacity = new_cap;
    }

    self->containers[self->size++] = c;
    printf("[Bucket Push] Object %p added to Bucket %p\n", (void*)c, (void*)self);
    return 1;
}

inline static cute_Container* 
cute_Bucket_pop(cute_ContainerBucket* self)
{
    if (self->size == 0) return NULL;
    cute_Container* c = self->containers[--self->size];
    printf("[Bucket Pop] Object %p removed from Bucket %p\n", (void*)c, (void*)self);
    return c;
}

void
cute_ContainerManager_init()
{

}

void
cute_ContainerManager_end()
{ 
	for (size_t i = Manager.size; i > 0; i--) 
	{ 
		cute_ContainerManager_throwBucket(); 
	} 
}

void
cute_ContainerManager_newBucket()
{
    if (Manager.size >= Manager.capacity) 
    {
        size_t new_cap = Manager.capacity ? Manager.capacity * 2 : 4;
        cute_ContainerBucket** tmp = realloc(Manager.buckets, sizeof(cute_ContainerBucket*) * new_cap);
        Manager.buckets = tmp;
        Manager.capacity = new_cap;
    }
    cute_ContainerBucket* bucket = cute_Bucket_new();
    Manager.buckets[Manager.size++] = bucket;
    printf("[Manager] New bucket %p added. Manager now has %zu buckets\n", (void*)bucket, Manager.size);
}


cute_Container* 
cute_ContainerManager_new(size_t size)
{
    cute_ContainerBucket* bucket = Manager.buckets[Manager.size-1];
    cute_Container* container = malloc(size);
    container->refcount = 1;
    container->destructor = NULL;
    container->bucket = bucket;

    cute_Bucket_push(bucket, container);
    printf("[Manager] New object %p added to Bucket %p\n", (void*)container, (void*)bucket);
    return container;
}

void
cute_ContainerManager_throwBucket()
{
    if (Manager.size == 0) {return;}

    cute_ContainerBucket* bucket = Manager.buckets[--Manager.size];
    printf("[Manager] Throwing Bucket %p\n", (void*)bucket);

    for (size_t i = 0; i < bucket->size; i++)
    {
        cute_Container* container = bucket->containers[i];

        if (container->refcount > 1)
        {
            container->refcount--;
            printf("[Manager] Object %p NOT removed, refcount now %zu\n", (void*)container, container->refcount);
        }
        else
        {
            if (container->destructor)
            {
                container->destructor(container);
            }
            printf("[Manager] Object %p removed from Bucket %p\n", (void*)container, (void*)bucket);
            free(container);
        }
    }

    cute_Bucket_del(bucket);
}


void
cute_ContainerManager_assign(cute_Container* src, cute_Container** dest)
{
	if (*dest != NULL)
	{
		// if dest was already assigned

		cute_Container* container = *dest;
		cute_Bucket_push(container->bucket, src);

		if (container->refcount > 1)
		{
			container->refcount--;
		}
		
	}

	src->refcount++;
	printf("%p refcount %ld\n", src, src->refcount);
	*dest = src;
}