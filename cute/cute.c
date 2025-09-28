#include "atoms/atoms.h"
#include "eval/eval.h"
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
	core->lexer = Lexer_new();
	core->parser = Parser_new();
	core->evaluator = EvaluatorContext_new();
	return core;
}

void CuteCore_Run(CuteCore* core)
{
	CuteCore_InvokeREPL(core);
}

void CuteCore_End(CuteCore* core)
{
	Lexer_del(core->lexer);
	Parser_del(core->parser);
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
		
		Lexer_init(core->lexer, buffer);
		TokenArray* tokens = Lexer_tokenize(core->lexer);
		TokenArray_print(tokens);
		Parser_init(core->parser, tokens);
		CuteAtomStack* stack = Parser_parse(core->parser);
		CuteAtomStack_print(stack);
		EvaluatorContext_init(core->evaluator, stack);
		CuteAtom atom = EvaluatorContext_evaluate(core->evaluator);
		CuteAtom_print(&atom, true);

	}
}