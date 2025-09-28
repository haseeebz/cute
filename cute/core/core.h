#include "../parser/node.h"
#include "../parser/parser.h"

#pragma once

typedef struct
{
	Parser* parser;
} CuteCore;

CuteCore CuteCore_setup();
void CuteCore_run(CuteCore* core);
void CuteCore_end(CuteCore*);