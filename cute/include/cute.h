#include "containers.h"
#include "tokenizer.h"
#include "parser.h"
#include "eval.h"

#pragma once

typedef struct {
	TokenizerContext* tokenizer;
	ParserContext* parser;
	EvaluatorContext* evaluator;
} Cute;


Cute* Cute_init();
void Cute_end(Cute* cute);
void Cute_run(Cute* cute, char* string);