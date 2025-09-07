#include "containers.h"
#include "tokenizer.h"
#include "parser.h"
#include "eval.h"

#pragma once

extern char CUTE_VERSION[];
extern char CUTE_NAME[];


typedef struct {
	TokenizerContext* tokenizer;
	ParserContext* parser;
	EvaluatorContext* evaluator;
} Cute;


Cute* Cute_init();
void Cute_end(Cute* cute);
void Cute_run(Cute* cute, int argc, char *argv[]);

void Cute_invokeREPL(Cute* cute);
void Cute_interpretString(Cute* cute, char* string);