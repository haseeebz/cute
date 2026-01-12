#include <stdio.h>

#include "CuteLib.h"
#include "CuteContainer.h"

#include "../internal/logs.h"


static cute_ContainerManager Manager;

void
cute_ContainerManager_init()
{
	Manager.global_bucket_count = 0;
	Manager.buckets_size = 0;
	Manager.buckets_capacity = 0;
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
	self->containers = NULL;
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
        cute_Container** tmp = realloc(self->containers, sizeof(cute_Container*) * new_cap);
        if (!tmp) return 0;
        self->containers = tmp;
        self->capacity = new_cap;
    }

    self->containers[self->size++] = c;
    return 1;
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
	bucket->rank = Manager.buckets_size;

	logs_logMessage(
		"containers",
		logs_level_info,
		"New bucket allocated %p (id:%zu). Rank: %zu. Total bucket count: %zu", 
		bucket, bucket->id, bucket->rank, Manager.buckets_size
	);
}


void
cute_ContainerManager_throwBucket()
{
    if (Manager.buckets_size == 0) {return;}

    cute_ContainerBucket* bucket = Manager.buckets[--Manager.buckets_size];

	logs_logMessage(
		"containers",
		logs_level_debug,
		"Throwing bucket %p (id:%zu)", bucket, bucket->id
	);

    for (size_t i = 0; i < bucket->size; i++)
    {
        cute_Container* container = bucket->containers[i];

		container->refcount--;

        if (container->refcount > 0)
        {
			logs_logMessage(
				"containers",
				logs_level_debug,
				"Container's %p refcount decreased. (now:%zu)", container, container->refcount
			);
        }
        else
        {
			cute_ContainerManager_del(container);
            logs_logMessage(
				"containers",
				logs_level_info,
				"Container %p deallocated upon refcount reaching zero.", container
			);
        }
    }


	logs_logMessage(
		"containers",
		logs_level_info,
		"Successfully threw bucket %p (id:%zu)", bucket, bucket->id
	);

    cute_Bucket_del(bucket);
}


cute_Container* 
cute_ContainerManager_new(size_t size)
{
    cute_ContainerBucket* bucket = Manager.buckets[Manager.buckets_size-1];
    cute_Container* container = malloc(size);
    container->refcount = 0;
    container->destructor = NULL;
    container->bucket = bucket;

	logs_logMessage(
		"containers",
		logs_level_info,
		"New container %p allocated. Added to bucket %p (id:%zu)", container, bucket, bucket->id
	);

    cute_Bucket_push(bucket, container);

    return container;
}


void 
cute_ContainerManager_del(cute_Container* container)
{
	if (container->refcount > 0)
	{
		logs_logMessage(
		"containers",
		logs_level_warning,
		"Container %p was deleted despite having %zu references.", container, container->refcount
		);
	}

	if (container->destructor)
	{
		container->destructor(container);
	}

	free(container);
}


void
cute_ContainerManager_assign(cute_Container* src, cute_Container** dest)
{
	
	if (*dest != NULL)
	{
		// if dest was already assigned

		cute_Container* dest_con = *dest;

		cute_Bucket_push(dest_con->bucket, src);

		if (dest_con->refcount >= 1)
		{
			dest_con->refcount--;
		}
		
		logs_logMessage(
			"containers",
			logs_level_debug,
			"Container's %p refcount was decreased due to assigning. (now:%zu)", *dest, (*dest)->refcount
		);

		// 1 has a higher rank than 2
		if (dest_con->bucket->rank < src->bucket->rank)
		{
			logs_logMessage(
				"containers",
				logs_level_info,
				"Container %p was moved from bucket %p to bucket %p due to higher rank.", 
				src, src->bucket, dest_con->bucket
			);
			src->bucket = dest_con->bucket;
		}


		if (dest_con->refcount == 0)
		{
			logs_logMessage(
				"containers",
				logs_level_info,
				"Container %p deallocated upon refcount reaching zero due to assignment.", dest_con
			);
			cute_ContainerManager_del(dest_con);
		}
	}
	else
	{
		// if dest is null, we assume the assigning is happening within the same bucket as the declaration
	}

	src->refcount++;
	*dest = src;

	logs_logMessage(
		"containers",
		logs_level_debug,
		"Container %p was assigned successfully. (refcount:%zu)", src, src->refcount
	);

}