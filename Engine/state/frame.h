#include "CuteAtom.h"


typedef struct
{
	CtAtom* locals;
	uint32_t locals_cap;
} ctFuncFrame;

