
#pragma once

#include "CuteIO.h"


static const char* logs_color_black   = "\x1b[30m";
static const char* logs_color_red     = "\x1b[31m";
static const char* logs_color_green   = "\x1b[32m";
static const char* logs_color_yellow  = "\x1b[33m";
static const char* logs_color_blue    = "\x1b[34m";
static const char* logs_color_magenta = "\x1b[35m";
static const char* logs_color_cyan    = "\x1b[36m";
static const char* logs_color_white   = "\x1b[37m";

static const char* logs_color_bright_black   = "\x1b[90m";
static const char* logs_color_bright_red     = "\x1b[91m";
static const char* logs_color_bright_green   = "\x1b[92m";
static const char* logs_color_bright_yellow  = "\x1b[93m";
static const char* logs_color_bright_blue    = "\x1b[94m";
static const char* logs_color_bright_magenta = "\x1b[95m";
static const char* logs_color_bright_cyan    = "\x1b[96m";
static const char* logs_color_bright_white   = "\x1b[97m";

static const char* logs_color_reset = "\x1b[0m";


typedef enum 
{
	logs_level_debug,
	logs_level_info,
	logs_level_warning,
	logs_level_critical,
	logs_level_error,
} logs_Level;

static logs_Level logs_minimumLevel;

void logs_logMessage(const char* name, logs_Level level, const char* msg, ...);

