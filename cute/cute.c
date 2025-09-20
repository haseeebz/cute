#include "atoms/atoms.h"
#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include "parser/parser.h"

#include "cute.h"
#include <stdio.h>
#include <stdlib.h>


CuteCore* CuteCore_Init()
{
	CuteCore* core = malloc(sizeof(CuteCore));
	core->lexer = LexerContext_new();
	core->parser = ParserContext_new();
	return core;
}

void CuteCore_Run(CuteCore* core)
{
	CuteCore_InvokeREPL(core);
}

void CuteCore_End(CuteCore* core)
{
	LexerContext_del(core->lexer);
	ParserContext_del(core->parser);
	free(core);
}


void CuteCore_InvokeREPL(CuteCore* core)
{
	char buffer[256] = {0};

	printf("Cute Shell\n");

	while (true)
	{
		printf(">> ");
		fgets(buffer, sizeof(buffer), stdin);
		printf("%s\n", buffer);
	}
}