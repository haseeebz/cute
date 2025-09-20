#include "cute.h"

int main()
{
	CuteCore* core = CuteCore_Init();
	CuteCore_Run(core);
	CuteCore_End(core);
	return 0;
}