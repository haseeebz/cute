#include <stdbool.h>
#include "containers.h"

#pragma once

typedef struct {
	char* current_string;
	int index;
	int string_size;
	ContainerStack* stack;
} TokenizerContext;



TokenizerContext* newTokenizerContext();
void initTokenizerContext(TokenizerContext* tokenizer, char* string);
void delTokenizerContext(TokenizerContext* tokenizer);

char TokenizerContext_nextToken(TokenizerContext* tokenizer);
void TokenizerContext_backtrackToken(TokenizerContext* tokenizer);

ContainerStack* TokenizerContext_tokenize(TokenizerContext* tokenizer, char* string);
void TokenizerContext_tokenizeNumber(TokenizerContext* tokenizer, char c);
void TokenizerContext_tokenizeOperator(TokenizerContext* tokenizer, char c);

