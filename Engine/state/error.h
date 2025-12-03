#include <stdint.h>


#pragma once

typedef struct
{
	char *name;
	uint32_t name_len;
	char *msg;
	uint32_t msg_len;
} ctError;

void ctError_new(ctError *error, char *name, char *msg);
void ctError_free(ctError *error);