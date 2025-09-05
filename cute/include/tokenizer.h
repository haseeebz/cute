#include <stdbool.h>
#include "containers.h"

#pragma once

typedef struct {
	char* current_string;
	int index;
	ContainerStack* stack;
	Container previous_token;
} TokenizerContext;



TokenizerContext* newTokenizerContext(char* string);
void delTokenizerContext(TokenizerContext* tokenizer);

ContainerStack* tokenize(char* string);
