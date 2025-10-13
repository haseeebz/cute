#include "cuteInstr.h"
#include "cuteProgImg.h"
#include "cuteEngine.h"

int main()
{
	CuteEngine engine;
	CuteEngine_init(&engine,  ProgramImage);
	CuteEngine_run(&engine);
	CuteEngine_end(&engine);	
	return 0;
}