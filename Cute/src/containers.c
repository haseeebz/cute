#include <stdio.h>

#include "CuteLib.h"
#include "CuteContainer.h"

#include "../internal/logs.h"


static cute_ContainerManager Manager;

void
cute_ContainerManager_init()
{
	Manager.global_bucket_count = 0;
}

void
cute_ContainerManager_end()
{ 
	for (size_t i = Manager.buckets_size; i > 0; i--) 
	{ 
		cute_ContainerManager_throwBucket(); 
	} 
}



inline static cute_ContainerBucket* 
cute_Bucket_new() 
{
    cute_ContainerBucket* self = malloc(sizeof(cute_ContainerBucket));
    self->size = 0;
    self->capacity = 0;
    return self;
}

inline static void 
cute_Bucket_del(cute_ContainerBucket* self) 
{
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
    return 1;
}

inline static cute_Container* 
cute_Bucket_pop(cute_ContainerBucket* self)
{
    if (self->size == 0) return NULL;
    cute_Container* c = self->containers[--self->size];
    return c;
}


void
cute_ContainerManager_newBucket()
{
    if (Manager.buckets_size >= Manager.buckets_capacity) 
    {
        size_t new_cap = Manager.buckets_capacity ? Manager.buckets_capacity * 2 : 4;
        cute_ContainerBucket** tmp = realloc(Manager.buckets, sizeof(cute_ContainerBucket*) * new_cap);
        Manager.buckets = tmp;
        Manager.buckets_capacity = new_cap;
    }
    cute_ContainerBucket* bucket = cute_Bucket_new();
	bucket->id = Manager.global_bucket_count++;

    Manager.buckets[Manager.buckets_size++] = bucket;

	logs_logMessage(
		"containers",
		logs_level_info,
		"New bucket allocated [%p] (id:%zu)", bucket, bucket->id
	);
}


cute_Container* 
cute_ContainerManager_new(size_t size)
{
    cute_ContainerBucket* bucket = Manager.buckets[Manager.buckets_size-1];
    cute_Container* container = malloc(size);
    container->refcount = 1;
    container->destructor = NULL;
    container->bucket = bucket;

	logs_logMessage(
		"containers",
		logs_level_info,
		"New container [%p] allocated. Added to bucket [%p] (id:%zu)", container, bucket, bucket->id
	);

    cute_Bucket_push(bucket, container);

    return container;
}

void
cute_ContainerManager_throwBucket()
{
    if (Manager.buckets_size == 0) {return;}

    cute_ContainerBucket* bucket = Manager.buckets[--Manager.buckets_size];


    for (size_t i = 0; i < bucket->size; i++)
    {
        cute_Container* container = bucket->containers[i];

        if (container->refcount > 1)
        {
            container->refcount--;
			logs_logMessage(
				"containers",
				logs_level_debug,
				"Container's [%p] refcount decreased. (now:%zu)", container, container->refcount
			);
        }
        else
        {
            if (container->destructor)
            {
                container->destructor(container);
            }

            logs_logMessage(
				"containers",
				logs_level_info,
				"Container [%p] deallocated upon refcount reaching zero.", container
			);

            free(container);
        }
    }

	
	logs_logMessage(
		"containers",
		logs_level_info,
		"Throwing bucket [%p] (id:%zu)", bucket, bucket->id
	);

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
		
		logs_logMessage(
			"containers",
			logs_level_debug,
			"Container's [%p] refcount was decreased due to assigning. (now:%zu)", *dest, (*dest)->refcount
		);
	}

	src->refcount++;
	*dest = src;

	logs_logMessage(
		"containers",
		logs_level_info,
		"Container [%p] was assigned. (refcount:%zu)", src, src->refcount
	);

}