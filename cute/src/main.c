#include "../include/cute.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	Cute* cute = Cute_init();
	Cute_run(cute, argc, argv);
	Cute_end(cute);
	return 0;
}