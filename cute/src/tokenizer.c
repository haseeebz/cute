#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/containers.h"
#include "../include/tokenizer.h"



TokenizerContext* newTokenizerContext()
{
	TokenizerContext* tokenizer = malloc(sizeof(TokenizerContext));
	return tokenizer;
}


void initTokenizerContext(TokenizerContext* tokenizer, char* string)
{	
	tokenizer->index = 0;
	tokenizer->string_size = strlen(string);

	tokenizer->current_string = malloc(sizeof(char) * tokenizer->string_size);
	strcpy(tokenizer->current_string, string);

	tokenizer->stack = newContainerStack(tokenizer->string_size);
}


void delTokenizerContext(TokenizerContext* tokenizer)
{
	free(tokenizer->current_string);
	delContainerStack(tokenizer->stack);
	free(tokenizer);
}



char nextToken(TokenizerContext* tokenizer)
{
	char c = tokenizer->current_string[tokenizer->index];
	tokenizer->index++;
	return c;
}


void backtrackToken(TokenizerContext* tokenizer)
{
	if (tokenizer->index > 0) {tokenizer->index--;}
}


ContainerStack* tokenize(TokenizerContext* tokenizer, char* string)
{
	initTokenizerContext(tokenizer, string);
	
	while (tokenizer->index <= tokenizer->string_size) {

		char c = nextToken(tokenizer);

		if (c == ' ') {continue;}

		if (c >= '0' && c <= '9')
		{
			tokenizeNumber(tokenizer, c);
			continue;
		}

		tokenizeOperator(tokenizer, c);
	}

	return tokenizer->stack;
}


void tokenizeNumber(TokenizerContext* tokenizer, char c)
{
	int integar = c - '0';

	while (1)
	{
		char next_c = nextToken(tokenizer);
		
		if (next_c >= '0' && next_c <= '9')
		{
			integar = (integar * 10) + (next_c - '0');
			continue;
		}

		backtrackToken(tokenizer);
		break;
	}

	ContainerStack_push(tokenizer->stack, newIntContainer(integar));
}


void tokenizeOperator(TokenizerContext* tokenizer, char c)
{
	Container con;

	switch (c) 
	{
		case '+' : con = newBinaryOpContainer(Add); break;
		case '-' : con = newBinaryOpContainer(Sub); break;
		case '*' : con = newBinaryOpContainer(Mul); break;
		case '/' : con = newBinaryOpContainer(Div); break;
		default  : return;
	}

	ContainerStack_push(tokenizer->stack, con);
}