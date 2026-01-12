#include <stdarg.h>
#include <stdio.h>

#include "logs.h"


void logs_logMessage(const char* name, logs_Level level, const char* msg, ...)
{
	va_list args;
	va_start(args, msg);

	printf("%s[%s]%s ", logs_color_blue, name, logs_color_reset);

	const char* color;
	const char* level_name;

	switch (level)
	{
        case logs_level_debug:
			color = logs_color_cyan;
			level_name = "debug";
			break;
        case logs_level_info:
			color = logs_color_green;
			level_name = "info";
			break;
        case logs_level_warning:
			color = logs_color_yellow;
			level_name = "warning";
			break;
        case logs_level_critical:
			color = logs_color_red;
			level_name = "critical";
			break;
        case logs_level_error:
			color = logs_color_bright_red;
			level_name = "error";
			break;
		default:
			color = logs_color_magenta;
			level_name = "unknown";
			break;
	};

    printf("%s(%s)%s ", color, level_name, logs_color_reset);
	vprintf(msg, args);
	printf("\n");
	va_end(args);
}