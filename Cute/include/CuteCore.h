
#pragma once 

struct cute_Core
{
	void (*main)();
};

void cute_Core_run(void (*main)());

void cute_Core_init();
void cute_Core_end();

