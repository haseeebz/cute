
#pragma once

#define CUTE_COMPILER_DEBUG_ENABLED

#ifdef CUTE_COMPILER_DEBUG_ENABLED
#include <iostream>
#define ctDebug(msg) (std::cout << (msg));
#else 
#define ctDebug(msg) ((void)0);
#endif