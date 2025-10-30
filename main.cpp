#include "CuteCompiler.hpp"
#include "CuteEngine.h"


int main()
{
    CuteEngine engine;
    CuteEngine_init(&engine);
    CuteEngine_run(&engine);
    CuteEngine_end(&engine);

	CuteCompiler compiler;
	compiler.compile("12 + 10");
	
    return 0;
}