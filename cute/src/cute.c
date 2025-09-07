#include <stdio.h>
#include <stdlib.h>
#include "../include/cute.h"
#include "../include/containers.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/eval.h"


Cute* initCute()
{
	Cute* cute = malloc(sizeof(Cute));
	cute->tokenizer = TokenizerContext_new();
	cute->parser = ParserContext_new();
	cute->evaluator = EvaluatorContext_new();
	return cute;
}


void endCute(Cute* cute)
{
	TokenizerContext_del(cute->tokenizer);
	ParserContext_del(cute->parser);
	EvaluatorContext_del(cute->evaluator);
	free(cute);
}

