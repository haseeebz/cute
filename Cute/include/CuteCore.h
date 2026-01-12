
#pragma once 

struct cute_Core
{
	void (*main)();
};

void cute_Core_run(void (*main)());

void cute_Core_init();
void cute_Core_end();


typedef enum
{
	cute_ExitCode_success = 0,
	cute_ExitCode_failure = 1
} cute_ExitCode;

void cute_Core_exit(cute_ExitCode code);

