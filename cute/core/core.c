#include "../parser/node.h"
#include "../parser/parser.h"

#include "core.h"
#include <stdio.h>


CuteCore CuteCore_setup()
{
	CuteCore core;
	core.parser = Parser_new();
	return core;
}

void CuteCore_run(CuteCore* core)
{
	char buffer[128];
	while (true)
	{
		printf(">>> ");
		fgets(buffer, sizeof(buffer),  stdin);
		Parser_init(core->parser, buffer);
		CuteNode* root = Parser_parse(core->parser);
		CuteNode_printRecursive(root);
		printf("\n");
	}
}


void CuteCore_end(CuteCore* core)
{
	Parser_del(core->parser);
}