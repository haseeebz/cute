#include "../include/cute.h"

int main()
{
	Cute* cute = Cute_init();
	Cute_run(cute, "12 + 12");
	Cute_end(cute);
	return 0;
}