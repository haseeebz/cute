#pragma once

#define CUTE_EXESTACK_LIMIT 512

#define CUTE_FUNCSTACK_LIMIT 256
#define CUTE_FUNCLOCALS_LIMIT 1024
#define CUTE_ARG_LIMIT 16


#define CUTE_DEBUG_ENABLED


#ifdef CUTE_DEBUG_ENABLED

#define ctDebug(str, ...) \
printf(str, __VA_ARGS__);

#else

#define ctDebug(str, ...) \
void(0);

#endif