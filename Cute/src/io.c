#include <stdio.h>
#include <stdarg.h>


#include "CuteIO.h"


void cute_Print(const char* string, ...)
{
	va_list args;
	va_start(args, string);

	vprintf(string, args);

	va_end(args);
}