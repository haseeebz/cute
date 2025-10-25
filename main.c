#include "CuteEngine.h"


int main()
{
    CuteEngine engine;
    CuteEngine_init(&engine);
    CuteEngine_run(&engine);
    CuteEngine_end(&engine);
    return 0;
}