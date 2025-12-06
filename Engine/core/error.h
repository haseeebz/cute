#include <stdint.h>


#pragma once

typedef struct
{
	char *name;
	uint32_t name_len;
	char *msg;
	uint32_t msg_len;
} ctError;


void error_new(ctError *error, char *name, char *msg);
void error_free(ctError *error);