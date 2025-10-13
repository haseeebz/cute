#include "cuteInstr.h"
#include "cuteProgImg.h"
#include "cuteEngine.h"

int main()
{
	CuteEngine engine;
	CuteEngine_init(&engine);
	CuteEngine_exec(&engine);
	CuteEngine_end(&engine);	
	return 0;
}