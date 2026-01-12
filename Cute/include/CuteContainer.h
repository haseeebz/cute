
#pragma once 

#include "stdlib.h"

struct _cute_Container;
struct _cute_ContainerBucket;

struct _cute_Container
{
	size_t refcount;
	struct _cute_ContainerBucket* bucket;
	void (*destructor)(struct _cute_Container*);
};

struct _cute_ContainerBucket
{
    struct _cute_Container** containers;  
    size_t size;
    size_t capacity;
};


typedef struct _cute_Container       cute_Container;
typedef struct _cute_ContainerBucket cute_ContainerBucket;


typedef struct
{
    cute_ContainerBucket** buckets;
    size_t size;
    size_t capacity;
} cute_ContainerManager;


void
cute_ContainerManager_init();

void
cute_ContainerManager_end();

void
cute_ContainerManager_newBucket();

void
cute_ContainerManager_throwBucket();

cute_Container* 
cute_ContainerManager_new(size_t size);

void
cute_ContainerManager_assign(cute_Container* src, cute_Container** dest);

void 
cute_ContainerManager_del(cute_Container* container);