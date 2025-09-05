#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/tokenizer.h"



TokenizerContext* newTokenizerContext(char* string)
{
	TokenizerContext* tokenizer = malloc(sizeof(TokenizerContext));

	tokenizer->stack = newContainerStack(strlen(string));
	tokenizer->previous_token = newVoidContainer();

	strcpy(tokenizer->current_string, string);
	tokenizer->index = 0;

	return tokenizer;
}


void delTokenizerContext(TokenizerContext* tokenizer)
{
	free(tokenizer->current_string);
	delContainerStack(tokenizer->stack);
	free(tokenizer);
}



ContainerStack* tokenize(char* string)
{
	
}
