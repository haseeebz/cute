#include "cute.h"

int main()
{
	CuteCore core = CuteCore_setup();
	CuteCore_run(&core);
	CuteCore_end(&core);
	return 0;
}