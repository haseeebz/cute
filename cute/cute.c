#include "atoms/atoms.h"
#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include "parser/parser.h"

#include "cute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
		char* newline = strchr(buffer, '\n');
		*newline = 0;

		LexerContext_init(core->lexer, buffer);
		TokenArray* tokens = LexerContext_tokenize(core->lexer);
		TokenArray_print(tokens);
		ParserContext_init(core->parser, tokens);
		CuteAtomStack* stack = ParserContext_parse(core->parser);
		CuteAtomStack_print(stack);
	}
}