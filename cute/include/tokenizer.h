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

char nextToken(TokenizerContext* tokenizer);
void backtrackToken(TokenizerContext* tokenizer);

ContainerStack* tokenize(TokenizerContext* tokenizer, char* string);
void tokenizeNumber(TokenizerContext* tokenizer, char c);
void tokenizeOperator(TokenizerContext* tokenizer, char c);

