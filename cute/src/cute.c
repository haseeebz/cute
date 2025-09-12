#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/atom.h"
#include "../include/cute.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/eval.h"


char CUTE_VERSION[] = "0.1.1";
char CUTE_NAME[] = "cute cat";
bool DEBUG = false;


Cute* Cute_init()
{
	Cute* cute = malloc(sizeof(Cute));
	cute->tokenizer = TokenizerContext_new();
	cute->parser = ParserContext_new();
	cute->evaluator = EvaluatorContext_new();
	return cute;
}


void Cute_end(Cute* cute)
{
	TokenizerContext_del(cute->tokenizer);
	ParserContext_del(cute->parser);
	EvaluatorContext_del(cute->evaluator);
	free(cute);
}


void Cute_run(Cute* cute, int argc, char *argv[])
{
	if (argc <= 1) 
	{
		Cute_invokeREPL(cute);
	}
}


void Cute_invokeREPL(Cute* cute)
{
	printf("Cute Interactive Shell (%s) [%s]\n", CUTE_VERSION, CUTE_NAME);

	char buffer[256];
	while (true)
	{
		printf(">> ");
		fgets(buffer, sizeof(buffer), stdin);
		Cute_interpretString(cute, buffer);
	}
}


void Cute_interpretString(Cute* cute, char* string)
{
	CuteAtomStack* tokenized_atoms = TokenizerContext_tokenize(cute->tokenizer, string);

	if (DEBUG) {CuteAtomStack_print(tokenized_atoms);}

	CuteAtomStack* parsed_atoms = ParserContext_parse(cute->parser, tokenized_atoms);

	if (DEBUG) {CuteAtomStack_print(parsed_atoms);}

	EvaluatorContext_evaluate(cute->evaluator, parsed_atoms);
	
	CuteAtom result = EvaluatorContext_yield(cute->evaluator);

	CuteAtom_print(&result, true);

	CuteAtomStack_del(tokenized_atoms);
	CuteAtomStack_del(parsed_atoms);
}