#include "CuteCompiler.hpp"
#include "CuteEngine.h"


int main()
{
	CuteCompiler compiler;
	compiler.compile("code.ct");


    CuteEngine engine;
    CuteEngine_init(&engine);
    CuteEngine_run(&engine);
    CuteEngine_end(&engine);
	
    return 0;
}