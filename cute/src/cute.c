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
	cute->tokenizer = newTokenizerContext();
	cute->parser = newParserContext();
	cute->evaluator = newEvaluatorContext();
	return cute;
}


void endCute(Cute* cute)
{
	delTokenizerContext(cute->tokenizer);
	delParserContext(cute->parser);
	delEvaluatorContext(cute->evaluator);
	free(cute);
}