#include "error.h"
#include <stdlib.h>
#include <string.h>


void ctError_new(ctError* error, char* name, char* msg)
{
	error->name_len = strlen(name);
	error->name = malloc(sizeof(char) * error->name_len);
	strncpy(error->name, name, error->name_len);

	error->msg_len = strlen(msg);
	error->msg = malloc(sizeof(char) * error->msg_len);
	strncpy(error->msg, msg, error->msg_len);
}

void ctError_free(ctError* error)
{
	if (error->msg)
	{
		free(error->msg);
	}

	if (error->name)
	{
		free(error->name);
	}
}