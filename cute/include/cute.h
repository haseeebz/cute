#include "containers.h"
#include "tokenizer.h"
#include "parser.h"
#include "eval.h"

typedef struct {
	TokenizerContext* tokenizer;
	ParserContext* parser;
	EvaluatorContext* evaluator;
} Cute;

Cute* initCute();
void endCute(Cute* cute);